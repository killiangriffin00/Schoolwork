// <copyright file="CellMediator.cs" company="Killian Griffin">
// Copyright (c) Killian Griffin. All rights reserved.
// </copyright>
namespace SpreadsheetEngine
{
    /// <summary>
    /// Superclass of <see cref="ConstantNode"/>, <see cref="OperatorNode"/>,
    /// and <see cref="VariableNode"/> that represents a node in an expression
    /// tree.
    /// </summary>
    public abstract class Node
    {
        /// <summary>
        /// Gives the value of the node, implementations
        /// are defined by child classes.
        /// </summary>
        /// <returns>
        /// <see cref="double"/>  representing the value of the node.
        /// </returns>
        public abstract double GetValue();
    }
}
