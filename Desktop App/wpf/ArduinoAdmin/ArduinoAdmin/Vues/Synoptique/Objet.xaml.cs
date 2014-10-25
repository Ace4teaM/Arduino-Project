using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace ArduinoAdmin.Vues.Synoptique
{
    /// <summary>
    /// Logique d'interaction pour Objet.xaml
    /// </summary>
    public partial class Objet : UserControl
    {
        public Objet()
        {
            InitializeComponent();
        }

        private void UserControl_MouseDown(object sender, MouseButtonEventArgs e)
        {
            ArduinoAdmin.VueModels.Synoptique.Objet obj = this.DataContext as ArduinoAdmin.VueModels.Synoptique.Objet;
            if (obj != null)
            {
                if (e.RightButton == MouseButtonState.Pressed && obj.RightClick != null)
                    obj.RightClick();
                else if(obj.Click != null)
                    obj.Click();
            }
        }
    }
}
