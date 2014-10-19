using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using ArduinoAdmin.Lib;

namespace ArduinoAdmin.Equipements.Model
{
    public class Server : ArduinoAdmin.Lib.Model
    {
        public IPAddress Ip { get; set; }
        public Server()
        {
        }

        public void SendMessage(Message message)
        {
            Console.WriteLine("SendMessage:"+message.ToString());
            if (Ip != null)
            {
                EthernetSocket eth = new EthernetSocket(Ip);
                eth.SendMessage(message);
            }
        }
    }
}
