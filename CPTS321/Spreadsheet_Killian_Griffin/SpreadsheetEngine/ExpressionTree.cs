// <copyright file="CellMediator.cs" company="Killian Griffin">
// Copyright (c) Killian Griffin. All rights reserved.
// </copyright>
namespace SpreadsheetEngine
{
    using System.ComponentModel;

    /// <summary>
    /// Stores and evaluates expressions, with <see cref="ConstantNode"/>s
    /// representing constant values, <see cref="VariableNode"/>s representing
    /// variables, and <see cref="OperatorNode"/>s representing operators combining
    /// these values.
    /// </summary>
    public class ExpressionTree : INotifyPropertyChanged
    {
        private Node root;
        private OperatorNodeFactory factory;
        private List<string> variableNames;
        private Dictionary<string, double> variables;

        /// <summary>
        /// Initializes a new instance of the <see cref="ExpressionTree"/> class.
        /// </summary>
        /// <param name="expression">
        /// <see cref="string"/> representing the expression to put in
        /// the expression tree.
        /// </param>
        public ExpressionTree(string expression)
        {
            this.variables = new Dictionary<string, double>();
            this.factory = new OperatorNodeFactory();
            this.variableNames = new List<string>();
            this.root = this.Parse(expression);
        }

        public event PropertyChangedEventHandler PropertyChanged = (sender, e) => { };

        /// <summary>
        /// Initializes a new instance of the <see cref="ExpressionTree"/> class.
        /// </summary>
        public ExpressionTree()
        {
            this.variables = new Dictionary<string, double>();
            this.factory = new OperatorNodeFactory();
            this.variableNames = new List<string>();
        }

        private Node Parse(string expression)
        {
            PostfixExpressionConverter converter = new PostfixExpressionConverter();
            List<Node> postfix = converter.PostfixConvert(expression, ref this.variables);
            List<Node> stack = new List<Node>();

            for (int i = 0; i <= postfix.Count() - 1; i++)
            {
                if (postfix[i] is ConstantNode)
                {
                    stack.Add(postfix[i]);
                }
                else if (postfix[i] is VariableNode)
                {
                    stack.Add(postfix[i]);
                    this.variableNames.Add(((VariableNode)postfix[i]).Name);

                }
                else if (postfix[i] is OperatorNode)
                {
                    OperatorNode newOperator = (OperatorNode)postfix[i];
                    newOperator.Right = stack.Last();
                    stack.RemoveAt(stack.Count() - 1);
                    newOperator.Left = stack.Last();
                    stack.RemoveAt(stack.Count() - 1);
                    stack.Add(newOperator);
                }
            }

            if (stack.Count <= 0)
            {
                return this.root;
            }

            return stack[0];
        }

        /// <summary>
        /// Stores or sets a variable in the <see cref="ExpressionTree"/> variable
        /// dictionary.
        /// </summary>
        /// <param name="variableName">
        /// Denotes the name or key of the variable in the dictionary.
        /// </param>
        /// <param name="variableValue">
        /// Denotes the value of the variable in the dictionary.
        /// </param>
        public void SetVariable(string variableName, double variableValue)
        {
            string caseIndependent = variableName.ToLower();
            this.variables[caseIndependent] = variableValue;
            this.PropertyChanged(this, new PropertyChangedEventArgs("Variable changed"));
        }

        /// <summary>
        /// Gets the name fields of all variables in the expression.
        /// </summary>
        /// <returns>
        /// <see cref="List{string}"/> of variable names in expression.
        /// </returns>
        public List<string> GetVariableNames()
        {
            return this.variableNames;
        }

        /// <summary>
        /// Evaluates the product of the given expression.
        /// </summary>
        /// <returns>
        /// <see cref="double"/> representing the result of the
        /// expression tree.
        /// </returns>
        public double Evaluate()
        {
            return this.root.GetValue();
        }

        /// <summary>
        /// Event handler for setting appropriate variable on its corresponding
        /// <see cref="Cell"/> changing.
        /// </summary>
        /// <param name="sender">
        /// Denotes <see cref="Cell"/> that was changed.
        /// </param>
        /// <param name="e">
        /// Denotes property change info.
        /// </param>
        public void CellVariablePropertyChangedEventHandler(object sender, PropertyChangedEventArgs e)
        {
            Cell changedCell = sender as Cell;
            try
            {
                string column = ((char)(changedCell.ColumnIndex + 65)).ToString();
                string row = (changedCell.RowIndex + 1).ToString();
                this.SetVariable(column + row, double.Parse(changedCell.Value));
            }
            catch (FormatException)
            {
            }
        }
    }
}
