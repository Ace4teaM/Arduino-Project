using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace ArduinoAdmin.Lib
{
    public class EthernetSocket
    {
        private UdpClient udpClient;
        private readonly int InputPort = 12345;
        private readonly int OutputPort = 8888;
        public EthernetSocket(IPAddress ArduinoAddress)
        {
            udpClient = new UdpClient();
            udpClient.Connect(ArduinoAddress, OutputPort);
        }
        ~EthernetSocket()
        {
            udpClient.Close();
        }
        public bool SendMessage(Message message)
        {
            Byte[] text = Encoding.ASCII.GetBytes(message.GetBuffer());
            udpClient.Send(text, text.Length);
            return true;
        }
        public Message ReceiveMessage(IPAddress ArduinoAddress)
        {
            //IPEndPoint object will allow us to read datagrams sent from any source.
            IPEndPoint RemoteIpEndPoint = new IPEndPoint(ArduinoAddress, InputPort);

            // Blocks until a message returns on this socket from a remote host.
            Byte[] receiveBytes = udpClient.Receive(ref RemoteIpEndPoint);
            string returnData = Encoding.ASCII.GetString(receiveBytes);

            return new Message(returnData);
        }

    }
}
