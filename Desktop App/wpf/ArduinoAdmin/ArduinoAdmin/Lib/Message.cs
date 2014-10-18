using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ArduinoAdmin.Lib
{
    class Message
    {
        private string buf;
        public Dictionary<string, string> Parameters{get;set;}
        private readonly char endOfParamName = '=';
        private readonly char endOfParamValue = ';';

        public enum MessageType
        {
            Command = 0,
            Configuration
        }

        public Message(MessageType type)
        {
            string strType;
            switch (type)
            {
                case MessageType.Command:
                    strType="CMD";
                    break;
                case MessageType.Configuration:
                    strType = "CFG";
                    break;
                default:
                    new ApplicationException("UnsupportedMessageType");
                    return;
            }
            this.buf = "MSG" + strType;
            //initialise le dictionnaire de paramètres
            this.Parameters = new Dictionary<string, string>();
        }

        public Message(string data)
        {
            this.buf = data.Substring(0,6);
            // eclate les arguments
            this.Parameters = data.Substring(6)
                .Split(';')
                .Select(part => part.Split(this.endOfParamName))
                .Where(part => part.Length == 2)
                .ToDictionary(sp => sp[0].ToUpper(), sp => sp[1]);
            Console.WriteLine(this.Parameters);
        }

        public string GetBuffer()
        {
            string strParam = String.Join(""+this.endOfParamValue, this.Parameters.Select(x => x.Key.ToUpper() + this.endOfParamName + x.Value).ToArray());
            return this.buf + strParam;
        }

        // ecrit la signature
        public bool EcrireSignature()
        {
            buf += "MSG";
            return true;
        }

        // lit la signature
        public int LireSignature(int ofs)
        {
            //lit la signature
            if (buf.Substring(ofs, 3) == "MSG")
                return ofs + 3;
            return 0;
        }

        // ecrit la signature
        public int EcrireParam(int ofs, string nom, string valeur)
        {
            string data = nom + this.endOfParamName + valeur + this.endOfParamValue;
            //ecrit les données
            buf += data;

            return ofs + data.Length;
        }

        // lit un parametre
        public int LireParam(int ofs, out string nom, out string valeur)
        {
            int endOfBuf = buf.Length;
            //lit le nom
            nom = "";
            while (ofs < endOfBuf && buf[ofs] != this.endOfParamName)
            {
                nom += buf[ofs];
            }
            ofs++;

            //lit la valeur
            valeur = "";
            while (ofs < endOfBuf && buf[ofs] != this.endOfParamValue)
            {
                valeur += buf[ofs];
            }
            ofs++;

            return ofs;
        } 
    }
}
