// Copyright (c) Killian Griffin. All Rights Reserved.

namespace HW2
{
    /// <summary>
    /// Contains the <see cref="HashSet(List{int})"/>,
    /// <see cref="InPlace(List{int})"/>, and <see cref="Sort(List{int})"/>
    /// methods.
    /// </summary>
    public class DistinctIntegersCalculator
    {
        /// <summary>
        /// Populates a hash set with the elements of the input list. The method
        /// uses the propery of the hash set of only unique elements being allowed
        /// to find the number of unique elements of the input list.
        /// </summary>
        /// <param name="input">
        /// List of integers for the number of unique elements to be calculated.
        /// </param>
        /// <returns>
        /// An <see cref="int"/> representing the number of unique elements in the
        /// input list.
        /// </returns>
        public static int HashSet(List<int> input)
        {
            HashSet<int> unique = new HashSet<int>();
            for (int i = 0; i < input.Count; i++)
            {
                unique.Add(input[i]);
            }

            return unique.Count();
        }

        /// <summary>
        /// Notes the size of the input list, then for each element in the input list
        /// iterates through the input list until the method finds a duplicate element.
        /// If one is found, decrements the noted size of the list until the list has
        /// been fully passed through and the noted size is equal to the number of distinct
        /// elements in the list.
        /// </summary>
        /// <param name="input">
        /// List of integers for the number of unique elements to be calculated.
        /// </param>
        /// <returns>
        /// An <see cref="int"/> representing the number of unique elements in the
        /// input list.
        /// </returns>
        public static int InPlace(List<int> input)
        {
            int unique = input.Count;

            for (int i = 0; i < input.Count; i++)
            {
                for (int j = i + 1; j < input.Count; j++)
                {
                    if (input[i] == input[j])
                    {
                        --unique;
                        break;
                    }
                }
            }

            return unique;
        }

        /// <summary>
        /// Sorts the input list using the <see cref="List{T}.Sort()"/> method, then
        /// iteraties through the list, storing and counting the current element each
        /// time it changes.
        /// </summary>
        /// <param name="input">
        /// List of integers for the number of unique elements to be calculated.
        /// </param>
        /// <returns>
        /// An <see cref="int"/> representing the number of unique elements in the
        /// input list.
        /// </returns>
        public static int Sort(List<int> input)
        {
            if (input.Count == 0)
            {
                return 0;
            }

            int unique = 1;
            input.Sort();
            for (int i = 1; i < input.Count; i++)
            {
                if (input[i] != input[i - 1])
                {
                    ++unique;
                }
            }

            return unique;
        }
    }
}
