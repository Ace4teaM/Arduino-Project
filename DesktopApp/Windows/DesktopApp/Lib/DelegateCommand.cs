using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Input;

namespace Lib
{
    class DelegateCommand : ICommand
    {

        #region private fields
        private readonly Action execute;
        private readonly Func<bool> canExecute;
        private object parameter;
        private EventHandler _internalCanExecuteChanged;
        #endregion

        public event EventHandler CanExecuteChanged
        {
            add
            {
                _internalCanExecuteChanged += value;
                if (this.canExecute != null)
                    CommandManager.RequerySuggested += value;
            }
            remove
            {
                _internalCanExecuteChanged -= value;
                if (this.canExecute != null)
                    CommandManager.RequerySuggested -= value;
            }
        }

        public void RaiseCanExecuteChanged()
        {
            if (canExecute != null)
                OnCanExecuteChanged();
        }
        protected virtual void OnCanExecuteChanged()
        {
            EventHandler eCanExecuteChanged = _internalCanExecuteChanged;
            if (eCanExecuteChanged != null)
                eCanExecuteChanged(this, EventArgs.Empty);
        }
        /// <summary>
        /// Contructeur
        /// </summary>
        /// <param name="execute">Action executée.</param>
        public DelegateCommand(Action execute)
        {
            this.execute = execute;
            this.canExecute = null;
        }

        /// <summary>
        /// Contructeur
        /// </summary>
        /// <param name="execute">Action executée.</param>
        /// <param name="canExecute">The execution status logic.</param>
        public DelegateCommand(Action execute, Func<bool> canExecute)
        {
            if (execute == null)
                throw new ArgumentNullException("execute");

            this.execute = execute;
            this.canExecute = canExecute;
        }

        public void Execute(object parameter)
        {
            this.parameter = parameter;
            this.execute();
        }

        public bool CanExecute(object parameter)
        {
            return this.canExecute == null ? true : this.canExecute();
        }
        public object GetParam()
        {
            return this.parameter;
        }
    }
}
