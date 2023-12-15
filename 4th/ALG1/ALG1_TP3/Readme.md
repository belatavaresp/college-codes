# Problem Description: Skateboard Maneuvers in Radlandia

## Description:
This problem revolves around calculating the maximum total score Dina can achieve by performing maneuvers in different sections of the skateboarding track in Radlandia. The input provides information about maneuver sections, including bonus factors and crossing times, as well as cataloged maneuvers with base scores and execution times. The goal is to output the maximum total score and the sequence of maneuvers performed in each section.

## Input Format
Each test case consists of several lines. The first line contains two integers, N and K, representing the number of maneuver sections of the track and the number of cataloged maneuvers in Radlandia. It is guaranteed that 1 ≤ N ≤ 100 and 1 ≤ K ≤ 10. Each of the following N lines describes a section of the track. The i-th of these lines contains two integers: ci, representing the bonus factor of the section (1 ≤ ci ≤ 100), and ℓi, representing the crossing time of the section (1 ≤ ℓi ≤ 106). Next, there are K lines, each describing a maneuver. The j-th of these lines contains two integers: the base score pj (-106 ≤ pj ≤ 106) of the maneuver and the time tj required to execute the maneuver (1 ≤ tj ≤ 106). Assume that the maneuvers are numbered from 1 to K in the order they are given in the input. Assume that Dina is brilliant in skateboard mechanics and can seamlessly connect one maneuver to another without any problem.

## Output Format
The output contains multiple lines. In the first line, a single integer T is printed, representing the maximum total score that Dina can achieve. Then, follow N lines, each with various integers. The i-th of these lines represents the i-th maneuver section. The first integer ni on this line represents the number of maneuvers that must be performed in the section; then, ni numbers should be printed, each representing a maneuver done in the i-th section.

The output should be written to the standard output.
