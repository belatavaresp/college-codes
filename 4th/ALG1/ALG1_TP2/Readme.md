# Problem Description: Optimal Network in Baiconia

## Description:
This problem revolves around finding optimal paths and years to travel between villages in Baiconia. The input provides information about village connections, construction years, travel times, and construction costs. The output should include minimum travel times to each village, the first year for mutually achievable distances, the first year to reach any village from the royal palace, and the minimum cost to connect the entire kingdom.

## Input Format
Each test case consists of several lines. The first line contains two integers, N and M, representing the number of villages and connections in Baiconia. It is guaranteed that the roads connect to form paths between every pair of villages. You can assume that 1 ≤ N, M ≤ 106, and the villages are numbered with elements from the set {1, 2, ..., N}. Each of the following M lines describes a connection between a pair of villages and contains five integers u, v, a, ℓ, c, where u and v are villages (1 ≤ u ≠ v ≤ N), a is the year of construction of the road (1 ≤ a ≤ 108), ℓ represents the travel time of the road (1 ≤ ℓ ≤ 105), and c represents its construction cost (1 ≤ c ≤ 105).

Assume that there are no other connections between villages, and Bacon - the Constructor - devised the plan in the year 0.

## Output Format
The output contains multiple lines. In the i-th of the first N lines, an integer is printed representing the minimum time required to travel from the royal palace to village i. On the N + 1-th line of the output, a single integer A1 is printed, representing the first year in which the distances listed in the previous lines are mutually achievable. The N + 2-th line of the output contains a single integer A2, representing the first year from which it is possible to reach any village in the kingdom from the royal palace. Finally, on the N + 3-th line, print a single integer representing the minimum cost required to connect the entire kingdom.

The output should be written to the standard output.
