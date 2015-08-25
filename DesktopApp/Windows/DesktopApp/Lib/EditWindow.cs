using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using DesktopApp.View;

namespace Lib
{
    public class EditWindow : Window
    {
        public EditWindow()
        {
            this.Content = new EditView();
            this.Owner = Application.Current.MainWindow;
            this.WindowStartupLocation = WindowStartupLocation.CenterOwner;
            this.WindowStyle = WindowStyle.ToolWindow;
            this.SizeToContent = SizeToContent.WidthAndHeight;
            this.ResizeMode = ResizeMode.NoResize;
        }

        public EditWindow(string title, UIElement content) : this()
        {
            this.Title = title;

            if (content != null)
                this.View.AddView(content);
        }

        public EditView View
        {
            get
            {
                return (this.Content as EditView);
            }
        }
    }
}
