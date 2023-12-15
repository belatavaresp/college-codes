# Problem Description: NBA Rookie Stats Analysis

This problem involves implementing and comparing supervised (kNN) and unsupervised (k-Means) learning methods for analyzing NBA Rookie Stats. The dataset is divided into training and testing sets, and the results of both parts are analyzed and discussed.

## Dataset Attributes
- GP: Total games played
- MIN: Minutes played
- PTS: Points per game
- FGM: Field goals made
- FGA: Field goal attempts
- FG%: Field goal percentage
- 3PMade: 3-pointers made
- 3PA: 3-point attempts
- 3P%: 3-point percentage
- FTM: Free throws made
- FTA: Free throw attempts
- FT%: Free throw percentage
- OREB: Offensive rebounds
- DREB: Defensive rebounds
- REB: Total rebounds
- AST: Assists
- STL: Steals
- BLK: Blocks
- TOV: Turnovers
- TARGET_5Yrs: Binary response variable (1 if the career lasts at least 5 years, 0 otherwise)

## Part 1 - Supervised Learning (k-Nearest Neighbors)

### Task
The goal of this part is to implement the k-Nearest Neighbors (kNN) algorithm to classify whether an NBA rookie's career will last at least 5 years in the league. Use the NBA Rookie Stats dataset, which consists of 1,340 observations with various attributes.

## Part 2 - Unsupervised Learning (k-Means)

### Task
Implement the k-Means algorithm to cluster NBA rookies using only the attribute features (excluding the `TARGET_5Yrs` column). Test the algorithm with 2 different k values (2 and 3), printing the obtained centroids for each cluster. Additionally, check if there is any relationship between the obtained clusters and the original labels of the data.
