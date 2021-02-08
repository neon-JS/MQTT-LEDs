using System;

namespace MqttSerialConverter.Extension {
    public static class StringExtensions {
        public static char GetRandomChar(this string subject) 
        {
            if (subject == null) {
                throw new NullReferenceException(nameof(subject));
            }

            var randomGenerator = new Random();
            return subject[randomGenerator.Next(subject.Length)];
        }
    }
}