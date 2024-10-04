import { Command } from 'commander';
import { input } from '@inquirer/prompts';

//import the db
import { createConnection } from '../../config/dbConfig.js';

//establish the command
const viewRoutesCommand = new Command('view-routes');

// opperation of the command
viewRoutesCommand
    .description('View all trucking routes (Admin only)')
    .action(async () => {

        //astablish db connection
        const connection = await createConnection();

        //ask the user for their roles
        const role = await input({ message: 'Enter your role (user/Admin):' });
        
        //if the role is not admin then return
        if (role.toLowerCase() === 'admin') {
            try {

                //create an array to store results
                const [results] = await connection.query('SELECT * FROM routes');

                //print the results
                console.table(results);
            } 
            // return error if error
            catch (err) {
                console.error('Error retrieving routes:', err);
            } 
            //terminate the command
            finally {
                await connection.end();
                process.exit(0);
            }
        } else {
            console.log('Access denied. Admins only.');
        }
    });

export default viewRoutesCommand;
