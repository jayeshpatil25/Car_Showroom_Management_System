CAR Showroom Management System  

Stock details in showroom: Number of available car models with details like name, colour, fuel type, type of car (Hatchback, Sedan, etc.). 
=> Sold cars. 
=> Available cars in stock. 
=> Required stock. 

Car Recognition: The sales person will enter the customer details (Name, Mobile no, address, etc.) Car registration no, model no, color, type of car it will help the user to search the Car details and the required details of the customer. 
=> Servicing of car. previous and next. 
=> Amount of EMI. 
=> Insurance evaluation date.  

Car details: It contains the details like name of customer, Name of the Car. It will take data from car recognition database. Billing and Payment Detail will contain the details like Actual Amount to be paid, EMI. Searching is having the details of the customer.  

Sales person: Any sales person can login and search the details of the customer. It will show all details like customer Details, CAR name, payment type etc. 
=> Details of sales person. (Id, Name, DOB, address) 
=? Details of sale. (sales target, sales achieved, commission as per sale, list of customers) 
Note: These details of sales person are dependent on the complete sale of car in showroom. 

Assuming there are three showrooms of a car company maintaining separate data as above, write functions to do the following :  
=> Merge databases of stock and car details to create data for all the showrooms together. Keep the data sorted based on unique id for each database.  
=> Find the most popular car considering all three showrooms.  
=> Given a sales person’s name, find out the total amount of loan amount pending for the set of cars sold by the sales person.  
=> For every car model/brand, find out the most successful sales person to be awarded.  
=> Based on last 12 month’s history, if you need to predict sales of a given car brand in the next month (also given), come up with a scheme/function to do that.  
=> Sort the car’s sold data in ascending order as per the car sold date. 
=> Set the target to sales person and check is it achieved or not. 
=> Find the sales figures of a specific model of a car in a specific duration of dates. 
=> Generate the alert for the car buyer for the service due after every six months of date of purchase. 
=> Calculate the bill of service of a car based on labor and spare parts.  
