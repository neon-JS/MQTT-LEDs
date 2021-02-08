using System;
using MqttSerialConverter.Models;
using MqttSerialConverter.Services;
using MQTTnet.Client;
using System.Text;

namespace MqttSerialConverter
{
    class Program
    {
        static void Main(string[] args)
        {
            var config = new MqttConfig("<ENDPOINT>"); // TODO: Extract to file-based config
            var client = MqttService.CreateConnectedAsync(config).GetAwaiter().GetResult();

            client.UseApplicationMessageReceivedHandler(eventArgs =>
            {
                // TODO: Forward to Serial
                var message = eventArgs.ApplicationMessage;

                Console.WriteLine("Debug: Received message!");
                Console.WriteLine($"Topic: '{message.Topic}'");
                Console.WriteLine($"Payload: '{Encoding.UTF8.GetString(message.Payload)}'");
            });

            Console.WriteLine("MQTT client is listening. Press any key to shutdown.");
            Console.ReadKey();
            Console.Write("\nShutting down. ");
            client.DisconnectAsync().GetAwaiter().GetResult();
            Console.WriteLine("Bye.");
        }
    }
}