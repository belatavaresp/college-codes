# Problem Description: Finding Faces in a Planar Graph

##Description: The problem revolves around a planar graph where the goal is to find the faces of the graph. The input provides the graph's vertices, edges, and their coordinates on a Cartesian plane. The output should specify the number of faces and the circuits representing the edges of each face. The solution should consider the planar nature of the graph and ensure the correct adjacency of consecutive vertices in each face.

## Input Format
Each test case consists of several lines. The first line contains two integers, N and M, representing the number of vertices and edges of the input graph G. It is guaranteed that G is connected, 1 ≤ N, M ≤ 105, and V(G) = {1, 2, ..., N}. The i-th line of the input starts with two real numbers xi, yi, representing the coordinates of vertex i in the Cartesian plane; it is guaranteed that −104 ≤ xi, yi ≤ 104. On the same line, there is a positive integer di, representing the degree of vertex i. Still, on the same line, there are di integers between 1 and N, each corresponding to a neighbor of i; it is guaranteed that a vertex is not a neighbor of itself.

## Output Format
The first line of the output contains an integer F, which must be equal to the number of faces of G. The next F lines should correspond to the F faces of G; each line starts with an integer si, representing the size of the i-th face of G; then, there are si integers representing the circuit corresponding to the edge of the face. The order of the faces is not important, but consecutive vertices on the edge of the face must be adjacent.
