// <copyright file="CellMediator.cs" company="Killian Griffin">
// Copyright (c) Killian Griffin. All rights reserved.
// </copyright>
namespace SpreadsheetEngine
{
    using System.Reflection;

    /// <summary>
    /// Generates <see cref="OperatorNode"/> subclasses.
    /// </summary>
    public class OperatorNodeFactory
    {
        public Dictionary<char, Type> operators = new Dictionary<char, Type>();

        /// <summary>
        /// Initializes a new instance of the <see cref="OperatorNodeFactory"/> class.
        /// </summary>
        public OperatorNodeFactory()
        {
            this.TraverseAvailableOperators((op, type) => this.operators.Add(op, type));
        }

        private delegate void OnOperator(char op, Type type);

        /// <summary>
        /// Creates a new <see cref="OperatorNode"/> subclass
        /// based on character input.
        /// </summary>
        /// <param name="operatorChar">
        /// Denotes operator object to return.
        /// </param>
        /// <returns>
        /// Subclass of <see cref="OperatorNode"/> corresponding to
        /// character input.
        /// </returns>
        public OperatorNode CreateOperatorNode(char operatorChar)
        {
            if (this.operators.ContainsKey(operatorChar))
            {
                object operatorNodeObject = System.Activator.CreateInstance(this.operators[operatorChar]);
                if (operatorNodeObject is OperatorNode)
                {
                    return (OperatorNode)operatorNodeObject;
                }
            }

            throw new Exception("Unhandled operator");
        }

        private void TraverseAvailableOperators(OnOperator onOperator)
        {
            Type operatorNodeType = typeof(OperatorNode);
            foreach (var assembly in AppDomain.CurrentDomain.GetAssemblies())
            {
                IEnumerable<Type> operatorTypes =
                assembly.GetTypes().Where(type => type.IsSubclassOf(operatorNodeType));
                foreach (var type in operatorTypes)
                {
                    PropertyInfo operatorField = type.GetProperty("OperatorChar");
                    if (operatorField != null)
                    {
                        object value = operatorField.GetValue(Activator.CreateInstance(type, new ConstantNode(0), new ConstantNode(0)));
                        if (value is char)
                        {
                            char operatorSymbol = (char)value;
                            onOperator(operatorSymbol, type);
                        }
                    }
                }
            }
        }
    }
}
