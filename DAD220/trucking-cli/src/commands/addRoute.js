import { validateDriverName, validateTruckModel, validateTruckMake, validateTruckYear, validateStartingZIP, validateFinalZIP } from '../utils/validation.js';
import { getLocation } from '../utils/helperFunctions.js';

import { Command } from 'commander';
import { input } from '@inquirer/prompts';
import { createConnection } from '../../config/dbConfig.js';

const program = new Command();


const addRouteCommand = new Command('add-route')
    .description('Add a new trucking route')
    .action(async () => {
        try {
            const connection = await createConnection();

            const driver = await input ({
                message: 'Enter driver name:',
                validate: validateDriverName
            });

            const truck_model = await input ({
                message: 'Enter truck model:',
                validate: validateTruckModel
            });

            const truck_make = await input ({
                message: 'Enter truck make:',
                validate: validateTruckMake
            });

            const truck_year = await input ({
                message: 'Enter truck year:',
                validate: validateTruckYear
            });


            const startZIP = await input ({
                message: 'Enter start ZIP code:',
                validate: await validateStartingZIP
            });



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


            const start_location = await getLocation(startZIP);

            const end_location = await getLocation(endZIP);

            const query =  `INSERT INTO routes (driver, truck_model, truck_make, truck_year, start_location, end_location) 
                            VALUES (?, ?, ?, ?, ?, ?)`;

            await connection.query(query, [
                driver, truck_model, truck_make.toUpperCase(), truck_year, start_location, end_location
            ]);

            console.log('Route added successfully');
        } catch (error) {
            console.error('Error:', error);
        }
    });



export default addRouteCommand;