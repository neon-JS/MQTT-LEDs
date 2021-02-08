namespace MqttSerialConverter.Models
{
    public class MqttConfig
    {
        public string Endpoint { get; }
        public string? UserName { get; }
        public string? Password { get; }

        public MqttConfig(string endpoint, string? userName = null, string? password = null)
        {
            Endpoint = endpoint;
            UserName = userName;
            Password = password;
        }
    }
}