// <copyright file="CellMediator.cs" company="Killian Griffin">
// Copyright (c) Killian Griffin. All rights reserved.
// </copyright>
namespace SpreadsheetEngine
{
    /// <summary>
    /// Class that converts expression strings to postfix
    /// expression form.
    /// </summary>
    public class PostfixExpressionConverter
    {
        private List<Node> postfix;
        private List<OperatorNode> stack;

        /// <summary>
        /// Initializes a new instance of the <see cref="PostfixExpressionConverter"/> class.
        /// </summary>
        public PostfixExpressionConverter()
        {
            this.postfix = new List<Node>();
            this.stack = new List<OperatorNode>();
        }

        /// <summary>
        /// Method that converts a given expression string to
        /// postfix form, returning the expression as a <see cref="List{}"/>
        /// of <see cref="Node"/>s.
        /// </summary>
        /// <param name="expression">
        /// Denotes the expression to convert to postfix.
        /// </param>
        /// <param name="variables">
        /// Denotes the reference to the variables dictionary in the <see cref="ExpressionTree"/>.
        /// </param>
        /// <returns>
        /// <see cref="List{T}"/> of <see cref="Node"/>s representing postfix expression.
        /// </returns>
        public List<Node> PostfixConvert(string expression, ref Dictionary<string, double> variables)
        {
            OperatorNodeFactory factory = new OperatorNodeFactory();
            ArgumentException invalid = new ArgumentException("Expression invalid");
            for (int i = 0; i < expression.Count(); i++)
            {
                if (IsOperator(expression[i]))
                {
                    OperatorNode newNode = factory.CreateOperatorNode(expression[i]);
                    if (this.stack.Count() <= 0 || this.stack.Last().OperatorChar == '(')
                    {
                        this.stack.Add(newNode);
                    }
                    else if (this.stack.Last().Precedence < newNode.Precedence)
                    {
                        this.stack.Add(newNode);
                    }
                    else
                    {
                        while (this.stack.Count() != 0 && (this.stack.Last().Precedence >= newNode.Precedence))
                        {
                            this.postfix.Add(this.stack.Last());
                            this.stack.RemoveAt(this.stack.Count() - 1);
                        }

                        this.stack.Add(newNode);
                    }
                }
                else if (expression[i] == '(')
                {
                    this.stack.Add(factory.CreateOperatorNode(expression[i]));
                }
                else if (expression[i] == ')')
                {
                    while (this.stack.Last().OperatorChar != '(')
                    {
                        this.postfix.Add(this.stack.Last());
                        this.stack.RemoveAt(this.stack.Count() - 1);
                    }

                    this.stack.RemoveAt(this.stack.Count() - 1);
                }
                else
                {
                    try
                    {
                        ConstantNode newConstant = new ConstantNode(double.Parse(expression[i].ToString()));
                        this.postfix.Add(newConstant);
                    }
                    catch (FormatException)
                    {
                        if ((expression[i] >= 65 && expression[i] <= 90) || (expression[i] >= 97 && expression[i] <= 122))
                        {
                            string variableName = expression.Substring(i, 2);
                            VariableNode newVariable = new VariableNode(variableName, ref variables);
                            this.postfix.Add(newVariable);
                            ++i;
                        }
                        else
                        {
                            throw invalid;
                        }
                    }
                }
            }

            while (this.stack.Count() > 0)
            {
                if (this.stack.Last().OperatorChar == '(')
                {
                    throw invalid;
                }

                this.postfix.Add(this.stack.Last());
                this.stack.RemoveAt(this.stack.Count() - 1);
            }

            return this.postfix;
        }

        /// <summary>
        /// Checks if given character is a supported operator.
        /// </summary>
        /// <param name="target">
        /// Character method is checking for operator status.
        /// </param>
        /// <returns>
        /// <see cref="bool"/> determining operator status.
        /// </returns>
        public static bool IsOperator(char target)
        {
            char[] operators = new char[] { '+', '-', '*', '/' };
            if (operators.Contains(target))
            {
                return true;
            }

            return false;
        }
    }
}
