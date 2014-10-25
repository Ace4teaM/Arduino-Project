using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PrmNep.Lib
{
    /// <summary>
    /// Représente une classe configurable
    /// </summary>
    interface IConfigurable
    {
        string ReadVar(string name);
        string WriteVar(string name, string value);
        List<string> ListVar();
    }
}
