using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace PrmNep.Lib
{
    /// <summary>
    /// Fonctions utiles à la lecture et l'écriture des variables de configurations
    /// </summary>
    class Configurable
    {
        /// <summary>
        /// Liste les propriétés d'une classe en tant que variable de configuration
        /// </summary>
        /// <param name="instance">Classe parente des propriétés</param>
        /// <returns>Liste des noms de propriétés</returns>
        public static List<string> ListProperties(object instance)
        {
            List<string> list = new List<string>();

            Type myType = instance.GetType();
            IList<PropertyInfo> props = new List<PropertyInfo>(myType.GetProperties());

            foreach (PropertyInfo prop in props)
            {
                list.Add(prop.Name);
            }

            return list;
        }

        /// <summary>
        /// Lit la valeur d'une propriété
        /// </summary>
        /// <param name="instance">Classe parente des propriétés</param>
        /// <param name="name">Nom de la propriété</param>
        /// <returns>Valeur assigné à la propriété. Si String.Empty est retourné la valeur n'a pas put être convertie</returns>
        public static string ReadProperty(object instance, string name)
        {
            PropertyInfo p = instance.GetType().GetProperty(name);
            if (p != null)
                return p.GetValue(instance).ToString();
            return String.Empty;
        }

        /// <summary>
        /// Ecrit la valeur d'une propriété
        /// </summary>
        /// <param name="instance">Classe parente des propriétés</param>
        /// <param name="name">Nom de la propriété à modifier</param>
        /// <param name="value">Nouvelle valeur de la propriété</param>
        /// <returns>Paramètre 'value'</returns>
        /// <remarks>La convertion du typage est assuré pour les types de bases (Built-In)</remarks>
        public static string WriteProperty(object instance, string name, string value)
        {
            PropertyInfo p = instance.GetType().GetProperty(name);
            if (p != null)
            {
                if (p.PropertyType == typeof(string))
                {
                    p.SetValue(instance, value);
                }
                else if (p.PropertyType == typeof(int))
                {
                    int result;
                    if (int.TryParse(value, out result))
                        p.SetValue(instance, result);
                }
                else if (p.PropertyType == typeof(float))
                {
                    float result;
                    if (float.TryParse(value, out result))
                        p.SetValue(instance, result);
                }
                else if (p.PropertyType == typeof(double))
                {
                    double result;
                    if (double.TryParse(value, out result))
                        p.SetValue(instance, result);
                }
                else if (p.PropertyType == typeof(bool))
                {
                    bool result;
                    if (bool.TryParse(value, out result))
                        p.SetValue(instance, result);
                }
                else if (p.PropertyType == typeof(decimal))
                {
                    decimal result;
                    if (decimal.TryParse(value, out result))
                        p.SetValue(instance, result);
                }
                else if (p.PropertyType == typeof(uint))
                {
                    uint result;
                    if (uint.TryParse(value, out result))
                        p.SetValue(instance, result);
                }
                else if (p.PropertyType == typeof(long))
                {
                    long result;
                    if (long.TryParse(value, out result))
                        p.SetValue(instance, result);
                }
                else if (p.PropertyType == typeof(ulong))
                {
                    ulong result;
                    if (ulong.TryParse(value, out result))
                        p.SetValue(instance, result);
                }
                else if (p.PropertyType == typeof(short))
                {
                    short result;
                    if (short.TryParse(value, out result))
                        p.SetValue(instance, result);
                }
                else if (p.PropertyType == typeof(ushort))
                {
                    ushort result;
                    if (ushort.TryParse(value, out result))
                        p.SetValue(instance, result);
                }
                else if (p.PropertyType == typeof(byte))
                {
                    byte result;
                    if (byte.TryParse(value, out result))
                        p.SetValue(instance, result);
                }
                else if (p.PropertyType == typeof(sbyte))
                {
                    sbyte result;
                    if (sbyte.TryParse(value, out result))
                        p.SetValue(instance, result);
                }
                else if (p.PropertyType == typeof(char))
                {
                    char result;
                    if (char.TryParse(value, out result))
                        p.SetValue(instance, result);
                }
                else
                {
                    Console.WriteLine(String.Format("Configurable.WriteProperty: Unsuported Type '{0}' for property {1} of class {2}", p.PropertyType.ToString(), p.Name, instance.GetType().Name));
                }
            }
            return value;
        }
    }
}
