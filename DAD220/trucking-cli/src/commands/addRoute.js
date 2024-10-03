import { Command } from 'commander';
import { input } from '@inquirer/prompts';
import { createConnection } from '../../config/dbConfig.js';

const program = new Command();


const addRouteCommand = new Command('add-route')
    .description('Add a new trucking route')
    .action(async () => {
        try {
            const connection = await createConnection();

            const driver = await input({message: 'Enter driver name:'});
            const truck_model = await input({message: 'Enter truck model:'});
            const truck_make = await input({message: 'Enter truck make:'});
            const truck_year = await input({message: 'Enter truck year:'});
            const start_location = await input({message: 'Enter start location'});
            const end_location = await input({message: 'Enter end location'});
            const distance = await input({message: 'Enter approximate distance (mi)'})

            const query =  `INSERT INTO routes (driver, truck_model, truck_make, truck_year, start_location, end_location, distance) 
                            VALUES (?, ?, ?, ?, ?, ?, ?)`;

            await connection.query(query, [
                driver, truck_model, truck_make, truck_year, start_location, end_location, distance
            ]);

            console.log('Route added successfully');
        } catch (error) {
            console.error('Error:', error);
        }
    });



export default addRouteCommand;