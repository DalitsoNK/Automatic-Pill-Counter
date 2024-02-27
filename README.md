DESIGN AND DEVELOPMENT OF AN AUTOMATIC PHARMACEUTICAL PILL COUNTER WITH A DATA MANAGEMENT SYSTEM FOR LOW RESOURCE COUNTRIES


1.0 Introduction

1.1 BACKGROUND

Most medications in Malawi are shipped to patient care facilities in large bottles containing 500 to 5,000 pills from central medical stores [1]. However, unlike medication blister packs or smaller bottles, these bulk bottles must be counted before being distributed to patients. This process is called the medication distribution system. The medication distribution system in a pharmacy is the process that starts with the reception of prescriptions from healthcare providers such as doctors and ends with the dispensing of medication to patients [2]. According to an interview with a pharmacist who works at Nkhoma Mission Hospital in Malawi, this process involves receiving the prescription for the patient's medication by the pharmacy department, reviewing the prescription, which includes checking the dosage and frequency, verifying the prescriber's identity by checking the signature and phone number, retrieving the medication from the stores, manually counting the pills to fit the patient's dosage using a tray and spatula, labeling the medication, and counseling the patient on how to take the medication.

However, manual counting can make it difficult to accurately count drugs, which might result in medication errors that could have serious effects on patients. These medication errors are categorized in a number of ways. One of the ways in which these errors are classified is as wrong dosage errors, which occur when the dose administered is either 5% or more below or above the recommended amount. The other category is called extra dosage errors, which occur when a patient is given a higher dose than the prescribing doctor intended. Other errors are called organizational failures, and these are due to organizational rules, policies, and government procedures [3]. In the case of Malawi, the procedure was described earlier in the medication distribution system.

A study conducted in Swatini, a country in southern Africa, found that pharmacists make counting errors for three primary reasons. The first reason is exhaustion, which refers to physical or mental exhaustion in pharmacists. The second reason is distraction, which can be caused by anything from interruptions to noise to multitasking. Hurriedness is the third reason, which implies that pharmacists may rush through their work due to time constraints or a heavy workload [4].
Prescription pill quantities (e.g., 30, 60, 120) are typically counted with electronic counting machines in higher-income countries because it requires less effort, saves time, and is typically more accurate than counting pills by hand [5]. Electronic pill counting machines, on the other hand, are uncommon in low-resource settings due to their high cost and maintenance requirements, unreliable electricity, humid or hot environmental conditions, and security concerns about housing an expensive machine.

1.2 PROBLEM STATEMENT

In Malawi,the medication distribution system uses human labor. The human labor involves the pharmacist taking out pills from the pill dispensary, pouring them on a pill counting tray, and manually counting how many pills to dispense to the patient. This can result in adverse consequences such as medication errors (i.e., dispensing, prescription, and dosage errors) [6]. A study done in nine countries in Africa showed 57.4% of patients were negatively affected by prescribing errors [6], and a study done by the WHO stated the cost associated with medication errors has been estimated to be $42 billion [7]. The actual medication taken out of the pharmacy is not accounted for; therefore, this creates a loophole for theft since there are no records of pills taken out, leading to medication being wasted. Medication is also wasted during manual counting, for example, due to pill spillage when using pill counting trays, including when a pharmacist overcounts pills beyond the required dosage; hence, the extra pills are wasted.
During an interview that we conducted, a pharmacist informed us that they don't count how many pills have actually been dispensed but only take account of the pills that are remaining from the total batch that the pharmacy ordered. Therefore, with this setup, it is easy to forge numbers. The whole process is tedious, which affects the workflow by causing long lines and overdosage and underdosage due to miscounts [7]. A study done in eSwantini stated that time spent counting pills increases patient waiting time and causes pharmacists to burn out [4]. Therefore, there is a need to design and develop an automatic pharmaceutical pill counter with a data management system for low-resource countries.


2.0 Project description

2.1.0 OBJECTIVES

 2.1.1 MAIN OBJECTIVE

The goal of this project is to design and develop a system that automatically and accurately counts the numbers of pills of different sizes in order to overcome dosage errors.

2.1.2 SPECIFIC OBJECTIVES

To design and develop a system that accurately counts pills of different types and sizes as per user input dosage.
To design and develop a system that generates inventory records for the pills counted.
To design and develop a system that prevents pill contamination in the device.

OPERATION OF THE SYSTEM

After careful prototyping and testing, we encountered a significant challenge. The conveyor belt system and the IR sensor were not working together as expected. The IR sensor was mistakenly identifying the conveyor belt as an obstacle, which led to it not detecting any pills passing on the belt. After consulting, we decided to address this issue by removing the conveyor belt and attaching the IR sensor directly to the selector cup. This adjustment allowed us to overcome the problem and ensure the proper functioning of the pill counting system. After this adjustment, below is a detailed explanation of our system's operation.
Firstly, the user has to power on the system using a toggle switch. To dispense pills, the pharmacist inputs the name of the pills they want to dispense and the number of pills using a screen and keypad. Once the amount is entered, the system consists of a cylindrical-shaped container that stores pills 
 
This pill selector cup has two compartments; one for storing the pills and the other for pushing them out. The pill selector cup also has a rotatable base with different hole sizes that can accommodate different pill sizes, as shown in figure The rotatable base is connected to the stepper motor. The rotatable pill selector base then rotates, carrying a pill from the first compartment to the other compartment, which has an outlet. While rotating, the pill selector cup has a divider with a brush, as shown in figure 16, to push extra pills aside to avoid them from entering the second compartment. The goal is for one pill to move to the second compartment. The pill falls out of the outlet of the pill selector cup; the outlet is connected to an infrared sensor. 
  

The infrared sensor acts as a counting mechanism. As a pill passes through the sensor, an electrical signal is generated, and that is recorded as one pill. The value of pills counted by the infrared sensor is transmitted to an ESP32 microcontroller that has a Wi-Fi feature. This feature is used to manage the system's data management system that connects to a MYSQL database. The system is equipped with a data management system that stores information on all pills counted by the machine.
Whenever the pill counter dispenses pills, the value is transmitted to the database and stored. This serves as an inventory management system that helps pharmacists keep track of all pills. By using this system, pharmacists can manage their stock more effectively and efficiently, reducing the risk of running out of essential medication. Therefore, the pill dispenser system provides an effective solution for pharmacies to track their pill inventory, ensuring that they can always provide medication to patients when they need it.

