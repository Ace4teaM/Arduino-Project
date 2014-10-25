using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Media.Imaging;

namespace ArduinoAdmin.VueModels.Synoptique
{
    public class Objet : ArduinoAdmin.Lib.ModelBase
    {
        public Objet()
        {
            this.NameDock = Dock.Bottom;
        }
        public ArduinoAdmin.Model.Equipement Equipement { get; set; }
        public Action Click, RightClick;
        public Dock NameDock { get; set; }
        public string Name { get; set; }
        public BitmapImage ImageSource { get; set; }
        public double Width { get; set; }
        public double Height { get; set; }
        public double Left { get; set; }
        public double Top { get; set; }

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
    }
}
