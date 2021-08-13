In finishing our project, we managed to successfully compile and run our ./final program. That took in a starting Airport’s ID, and the destination Airport’s ID, which generated a path of airports using both A* Search and Dijkstra’s algorithm as well as the total distance traveled. As you can see below, this is two given outputs for BFS, Dijkstra’s and A* Search, for the two pairs of inputs: O’Hare airport to Northern Peninsula Airport, and Willard Airport to Batman Airport, where they were input in as 3830 and 3318, and 4049 and 1729 respectively.



## Input 1: O’Hare International Airport [3830] to Northern Peninsula Airport [3318]


**Dijkstra’s Output**


3830 Chicago O'Hare International Airport, United States, Distance from destination: 14048.9 km


3751 Denver International Airport, United States, Distance from destination: 12731.3 km


1 Goroka Airport, Papua New Guinea, Distance from destination: 630.159 km


5 Port Moresby Jacksons International Airport, Papua New Guinea, Distance from destination: 547.315 km


3322 Cairns International Airport, Australia, Distance from destination: 749.625 km


3318 Northern Peninsula Airport, Australia, Distance from destination: 0 km


Total flights: 5


Total distance traveled: 15580.5 km


Average airport distance from destination (excluding origin and destination): 3664.6


**A * Search Output**


3830 Chicago O'Hare International Airport, United States, Distance from destination: 14048.9 km


2279 Narita International Airport, Japan, Distance from destination: 5199.09 km


3322 Cairns International Airport, Australia, Distance from destination: 749.625 km


3318 Northern Peninsula Airport, Australia, Distance from destination: 0 km


Total flights: 3


Total distance traveled: 16705.3 km


Average airport distance from destination (excluding origin and destination): 2974.36




## Input 2: University of Illinois Willard Airport [4049] to Batman Airport [1729]


**Dijkstra’s Output**


4049 University of Illinois Willard Airport, United States, Distance from destination: 9930 km


3830 Chicago O'Hare International Airport, United States, Distance from destination: 9740.21 km


1613 Vienna International Airport, Austria, Distance from destination: 2279.82 km


1682 Esenboğa International Airport, Turkey, Distance from destination: 742.588 km


1729 Batman Airport, Turkey, Distance from destination: 0 km


Total flights: 4


Total distance traveled: 10105.1 km


Average airport distance from destination (excluding origin and destination): 4254.21


**A * Search Output**


4049 University of Illinois Willard Airport, United States, Distance from destination: 9930 km


3830 Chicago O'Hare International Airport, United States, Distance from destination: 9740.21 km


1701 Atatürk International Airport, Turkey, Distance from destination: 1108.13 km


1729 Batman Airport, Turkey, Distance from destination: 0 km


Total flights: 3


Total distance traveled: 10140 km


Average airport distance from destination (excluding origin and destination): 5424.17



From these outputs, you can see that our code is outputting correctly as it correctly generates a vector of airports that all correctly have associated routes to each other and efficiently minimizes the distance traveled between two airports. This was tested via google maps and finding the raw distance between the two pairs while using Haversines. In addition, this successfully answered our leading question as we were able to generate the shortest path between two airports. We discovered a few ideas about the specific methods. First, we found that A* Search often generates a larger total distance than Dijkstra, this is shown by the outputs above where we see that A* generates a total distance traveled of 16705.3 km for O’Hare to Northern Peninsula Airportwhile Dijkstra’s generates a total distance of 15580.5 km. Likewise, we also discovered that A* Search usually minimizes the total flights between two airports, this is shown through how our outputs for A* both have 3 airports while our Dijkstra’s outputs have more at 5 and 4. These two observations allow us to conclude that utilizing the results from the A* Search to plan a trip would minimize the amount of money you would spend on individual flights and minimize the amount of time you would spend at various airports reaching a connecting flight. This is useful for not only minimizing the amount of money spent, but also reducing the likelihood of delays since the more airports you would need to visit the higher the chance of a delay. 


To conclude, with successfully being able to answer our leading question and having a functional base code, our group is satisfied with the results we have achieved with this project. As a whole, our group enjoyed this project as it gave us a realistic and applicable example of a collaborative coding project that we would probably encounter in a future professional setting. Specifically, we liked the combination of coding and professional documentation between writing code and updating our development logs. But if we had more time, we would’ve incorporated the specific flights of a given airport and used that to find the most efficient flight and airport combination. 
