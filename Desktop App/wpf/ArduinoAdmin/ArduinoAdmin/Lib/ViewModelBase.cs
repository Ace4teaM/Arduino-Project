using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
using System.Diagnostics;
using System.Windows.Input;

namespace MVVM.Lib
{
    /// <summary>
    /// Base class for all ViewModel classes in the application. Provides support for 
    /// property changes notification.
    /// </summary>
    public abstract class ViewModelBase : INotifyPropertyChanged
    {
        /// <summary>
        /// Raised when a property on this object has a new value.
        /// </summary>
        public event PropertyChangedEventHandler PropertyChanged;
        
        /// <summary>
        /// Warns the developer if this object does not have a public property with
        /// the specified name. This method does not exist in a Release build.
        /// </summary>
        [Conditional("DEBUG")]
        [DebuggerStepThrough]
        public void VerifyPropertyName(string propertyName)
        {
            // verify that the property name matches a real,  
            // public, instance property on this object.
            if (TypeDescriptor.GetProperties(this)[propertyName] == null)
            {
                Debug.Fail("Invalid property name: " + propertyName);
            }
        }

        /// <summary>
        /// Raises this object's PropertyChanged event.
        /// </summary>
        /// <param name="propertyName">The name of the property that has a new value.</param>
        protected virtual void OnPropertyChanged(string propertyName)
        {
            this.VerifyPropertyName(propertyName);

            if (this.PropertyChanged != null)
            {
                this.PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }

        // obtient une propriete de commande
        public ICommand GetCommand(string name)
        {
            var stringProps = this
                .GetType()
                .GetProperties()
                .Where(p => p.PropertyType == typeof(ICommand));
            foreach (var prop in stringProps)
            {
                ICommand val = (ICommand)prop.GetValue(this);
                if (prop.Name == name)
                    return val;
            }
            return null;
        }

        // obtient une propriété
        public object GetProperty(string name)
        {
            var prop = this
                .GetType()
                .GetProperties()
                .Where(p => p.Name == name).FirstOrDefault();
            if (prop != null)
                return prop.GetValue(this);
            return null;
        }

        // définit une propriété
        public bool SetProperty(string name, object value)
        {
            var prop = this
                .GetType()
                .GetProperties()
                .Where(p => p.Name == name).FirstOrDefault();
            if (prop != null)
            {
                prop.SetValue(this, value);
                return true;
            }
            return false;
        }
    }
}
