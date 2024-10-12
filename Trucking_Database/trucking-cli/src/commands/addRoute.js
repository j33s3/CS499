
// imports functions from helper files
import { validateDriverName, validateTruckModel, validateTruckMake, validateTruckYear, validateStartingZIP, validateFinalZIP } from '../utils/validation.js';
import { getLocation } from '../utils/helperFunctions.js';
import { createConnection } from '../../config/dbConfig.js';

import { Command } from 'commander';
import { input } from '@inquirer/prompts';


// creates the new command
const addRouteCommand = new Command('add-route')
    .description('Add a new trucking route')
    .action(async () => {

        //create the connection to the db
        const connection = await createConnection();

        // gather all the filing info and insert it into the DB
        try {

            // ask for driver and validate
            const driver = await input ({
                message: 'Enter driver name:',
                validate: validateDriverName
            });

            //ask for model and validate
            const truck_model = await input ({
                message: 'Enter truck model:',
                validate: validateTruckModel
            });

            //ask for make and validate
            const truck_make = await input ({
                message: 'Enter truck make:',
                validate: validateTruckMake
            });

            //ask for year and validate
            const truck_year = await input ({
                message: 'Enter truck year:',
                validate: validateTruckYear
            });

            // ask for starting zip and validate
            const startZIP = await input ({
                message: 'Enter start ZIP code:',
                validate: await validateStartingZIP
            });


            //ask for destination zip and validate
            const endZIP = await input ({
                message: 'Enter end ZIP code:',
                validate: async (input) => {
                    const result = await validateFinalZIP(input, startZIP);
                    if(result !== true) {
                        return result;
                    }
                    return true;
                }
            });

            // convert the start/end zip to (*city*, *state abbr* *zip*)
            const start_location = await getLocation(startZIP);
            const end_location = await getLocation(endZIP);

            //Insertion query
            const query =  `INSERT INTO routes (driver, truck_model, truck_make, truck_year, start_location, end_location) 
                            VALUES (?, ?, ?, ?, ?, ?)`;

            // sends the query to the database
            await connection.query(query, [
                driver, truck_model, truck_make.toUpperCase(), truck_year, start_location, end_location
            ]);

            console.log('Route added successfully');
        } 
        // Catch errors
        catch (error) {
            console.error('Error:', error);
        } 
        // terminate program
        finally {
            await connection.end();
            process.exit(0);
        }
    });



export default addRouteCommand;