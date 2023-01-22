// <copyright file="CellMediator.cs" company="Killian Griffin">
// Copyright (c) Killian Griffin. All rights reserved.
// </copyright>
namespace SpreadsheetEngine
{
    /// <summary>
    /// Subclass of <see cref="Node"/> that represents a variable
    /// in an expression tree.
    /// </summary>
    internal class VariableNode : Node
    {
        private Dictionary<string, double> variables;

        /// <summary>
        /// Initializes a new instance of the <see cref="VariableNode"/> class.
        /// </summary>
        /// <param name="name">
        /// Denotes the name of the varible in the dictionary.
        /// </param>
        /// <param name="variables">
        /// Reference for values of given varible name.
        /// </param>
        public VariableNode(string name, ref Dictionary<string, double> variables)
        {
            this.Name = name;
            this.variables = variables;
            variables = this.variables;
        }

        /// <summary>
        /// Gets or sets the name property that represents the
        /// name of the variable in the <see cref="ExpressionTree"/>
        /// dictionary.
        /// </summary>
        public string Name { get; set; }

        /// <summary>
        /// Parent class method for getting the evaluated
        /// value of the node subclass.
        /// </summary>
        /// <returns>
        /// <see cref="double"/> representing the value of the
        /// operation.
        /// </returns>
        public override double GetValue()
        {
            return this.variables[this.Name.ToLower()];
        }
    }
}
