using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Windows.Media.Imaging;
using ArduinoAdmin.Lib;

namespace ArduinoAdmin.Equipements.Model
{
    class InternalLed : ArduinoAdmin.Lib.Model
    {
        public InternalLed()
        {
            switchOnBitmap = LoadBitmapFromResource("Ressources/Equipements/switch_on.png");
            switchOffBitmap = LoadBitmapFromResource("Ressources/Equipements/switch_off.png");
        }
        public Server ParentServer { get; set; }

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
                    if (value == true)
                        message.Parameters.Add("CodeCmd", "LEDH");
                    else if (value == false)
                        message.Parameters.Add("CodeCmd", "LEDL");
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
