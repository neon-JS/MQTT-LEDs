using System;
using System.Threading;
using System.Threading.Tasks;
using MQTTnet;
using MQTTnet.Client;
using MQTTnet.Client.Options;
using MqttSerialConverter.Models;
using MqttSerialConverter.Extension;

namespace MqttSerialConverter.Services
{
    public class MqttService
    {
        private const string CLIENT_ID_PREFIX = "Mqtt2Serial";
        private const int CLIENT_ID_MAX_LENGTH = 23;
        private const string CLIENT_ID_VALID_CHARS = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        
        private const int RECONNECTION_DELAY = 5; // seconds

        public static async Task<IMqttClient> CreateConnectedAsync(MqttConfig config)
        {
            var client = new MqttFactory().CreateMqttClient();

            client.UseDisconnectedHandler(async _ =>
            {
                Console.WriteLine("MQTT client disconnected from server!");
                await Task.Delay(TimeSpan.FromSeconds(RECONNECTION_DELAY));
                Console.WriteLine("MQTT client tries reconnecting.");

                try
                {
                    await client.ConnectAsync(client.Options, CancellationToken.None);
                }
                catch
                {
                    await Console.Error.WriteLineAsync("MQTT client could not reconnect!");
                }
            });

            client.UseConnectedHandler(async _ =>
            {
                Console.WriteLine("MQTT client connected! Subscribing to all topics.");

                var topicFilter = new MqttTopicFilterBuilder()
                    .WithTopic("#")
                    .Build();
                await client.SubscribeAsync(topicFilter);
            });

            await client.ConnectAsync(BuildClientOptions(config));

            return client;
        }

        private static IMqttClientOptions BuildClientOptions(MqttConfig config)
        {
            var clientOptionsBuilder = new MqttClientOptionsBuilder()
                .WithClientId(GenerateClientId())
                .WithTcpServer(config.Endpoint)
                .WithCleanSession();

            if (config.UserName != null)
            {
                clientOptionsBuilder.WithCredentials(config.UserName, config.Password);
            }

            return clientOptionsBuilder.Build();
        }

        private static string GenerateClientId()
        {
            var clientId = CLIENT_ID_PREFIX;

            while(clientId.Length < CLIENT_ID_MAX_LENGTH) {
                clientId += CLIENT_ID_VALID_CHARS.GetRandomChar();
            }

            return clientId;
        }
    }
}