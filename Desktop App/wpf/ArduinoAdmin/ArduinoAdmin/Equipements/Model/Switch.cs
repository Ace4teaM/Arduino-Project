using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Net;
using System.Reflection;
using System.Text;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using ArduinoAdmin.Lib;

namespace ArduinoAdmin.Equipements.Model
{
    public class Switch : ArduinoAdmin.Lib.Model
    {
        public Switch(Server ParentServer, int PinNumber)
        {
            switchOnBitmap = LoadBitmapFromResource("Ressources/Equipements/switch_on.png");
            switchOffBitmap = LoadBitmapFromResource("Ressources/Equipements/switch_off.png");
            this.PinNumber = PinNumber;
            this.ParentServer = ParentServer;
        }
        public Server ParentServer { get; set; }
        public int PinNumber { get; set; }

        public bool? state;
        public bool? State
        {
            get
            {
                return state;
            }
            set
            {
                //envoi la commande
                if (ParentServer != null)
                {
                    Message message = new Message(Message.MessageType.Command);
                    message.Parameters.Add("CodeCmd", "DOUT");
                    message.Parameters.Add("PinNum", PinNumber.ToString());
                    if (value == true)
                        message.Parameters.Add("Value", "1");
                    else if (value == false)
                        message.Parameters.Add("Value", "0");
                    ParentServer.SendMessage(message);
                }
                //lit le retour
                //..
                //actualise l'état
                state = value;
            }
        }
        public BitmapImage switchOnBitmap = new BitmapImage();
        public BitmapImage switchOffBitmap = new BitmapImage();
        public BitmapImage ImageSource
        {
            get
            {
                if (State == true)
                    return switchOnBitmap;
                return switchOffBitmap;
            }
        }
        public static BitmapImage LoadBitmapFromResource(string pathInApplication, Assembly assembly = null)
        {
            if (assembly == null)
            {
                assembly = Assembly.GetCallingAssembly();
            }

            if (pathInApplication[0] == '/')
            {
                pathInApplication = pathInApplication.Substring(1);
            }
            return new BitmapImage(new Uri(@"pack://application:,,,/" + assembly.GetName().Name + ";component/" + pathInApplication, UriKind.Absolute));
        }

        public void Push()
        {
            if (State == null)
                State = true;
            else
                State = !State;
            OnPropertyChanged("ImageSource");
        }
    }
}
