// <copyright file="CellMediator.cs" company="Killian Griffin">
// Copyright (c) Killian Griffin. All rights reserved.
// </copyright>
namespace SpreadsheetEngine
{
    /// <summary>
    /// Subclass of <see cref="Node"/> that represents a constant
    /// value in an expression tree.
    /// </summary>
    public class ConstantNode : Node
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="ConstantNode"/> class.
        /// </summary>
        /// <param name="value">
        /// Denotes the initial value of the node.
        /// </param>
        public ConstantNode(double value)
        {
            this.Value = value;
        }

        /// <summary>
        /// Gets or sets the value property that represents the
        /// value of the node.
        /// </summary>
        public double Value { get; set; }

        public override double GetValue() { return this.Value; }
    }
}
