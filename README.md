BitPet - Bitcoin Virtual Pet System ver 1.0 
by Joshua Kwan

<br>

// About

BitPet is a prototype virtual pet system inspired by Bitcoin.

BitPet grows by being connected to Bitcoin related twitter tweets and "feeding" upon them in real time. By selecting two different keywords as search parameters for the tweets, users are able to raise and evolve the BitPet according to the the types of public tweets being detected.

The concept behind BitPet is based upon people's expectations of Bitcoin's public image. By selecting two keywords as twitter search parameters (one based upon negative connotations, the other positive), BitPet will grow automatically and evolve into one of two paths dependent on the type of keywords detected. 

Will it evolve to the user's expectations, or surprise the user by evolving differently? BitPet aims to challenge people's expectations of what Bitcoin is normally associated with, in contrast with what the public is actually talking about on twitter regarding Bitcoin.

<br>

// Offline Mode Functions

Offline mode is used to demonstrate BitPet's basic functionality quickly without using NodeRed and waiting for twitter feeds. Aside from the lack of the twitter components, offline mode has the same functions as online mode.

To feed the BitPet when it appears, tap on the left half of the screen to feed a negative keyword tweet and the right half for the a positive keyword. The BitPet will evolve after every 5 tweets/taps (max two evolutions).

Pet statistics and Tweet statistics can be accessed on the bottom once the BitPet has appeared. BitPet can be restarted by accessing the question mark button on the bottom right.

<br>

// Online Mode Functions (Incomplete)

Currently the online mode is incomplete and is only used to demonstrate its connectivity by detecting public tweets with the word "Bitcoin". Once the BitPet is set up, it will automatically evolve after 5 tweets have been detected (Max 2 evolutions). The online mode can only evolve along one path currently.

Pet statistics and Tweet statistics can be accessed on the bottom once the BitPet has appeared. BitPet can be restarted by accessing the question mark button on the bottom right.

<br>

// Requirements

BitPet utilises an Arduino Uno along with a TFT Touch Shield V2 from Seeed Studio. Please download and add the associated libraries for TFT Touch Shield V2 from Seeed Studio's github.

Once added, place the Touch Shield on to the Arduino, upload the Arduino file and offline mode should be ready.

For online mode, BitPet BitPet utilises Node-RED. Please install and access Node-RED then import the Node-RED files within the Online Mode folder. Authenticate the twitter node with an account credential in order to detect tweets.

Upload the Arduino file then deploy the Node-RED flow. Online mode should then be ready.
