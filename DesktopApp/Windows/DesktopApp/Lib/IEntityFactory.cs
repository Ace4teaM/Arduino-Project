using System;
using System.Collections;
using System.Collections.Generic;
using System.Data.Common;
using System.Linq;
using System.Text;

namespace Lib
{
    public interface IEntityFactory
    {
        string Name { get; }
        IEntityPersistent GetReference(IEntityPersistent e);
        IEnumerable Factory<T>() where T : IEntityPersistent, new();
        void Commit(IEntityPersistent[] entities);
        List<IEntityPersistent> GetReferences();
        object QueryScalar(string query);
        int Query(string query);
        void Query(string query, Func<DbDataReader, int> act);
        void QueryObject(string query, object obj);
        string ParseType(object value);
    }
}