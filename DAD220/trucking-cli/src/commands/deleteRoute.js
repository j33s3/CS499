import { Command } from'commander';
import { input } from'@inquirer/prompts';

// imports functions from dbconfig and validation
import { createConnection } from'../../config/dbConfig.js';
import { validateIndexRemoval } from '../utils/validation.js';


// initializes the command
const deleteRouteCommand = new Command('delete-route');

// contents of the command
deleteRouteCommand
    .description('Delete a route by ID (Admin only)')
    .action(async() => {
        //asks the user to enter their role
        const role = await input({ message: 'Enter your role (user/Admin):'});

        //creates the db connection
        const connection = await createConnection();

        //checks that the user is admin
        if (role.toLowerCase() === 'admin') {
            const routeId = await input({ 
                message: 'Enter the route ID to delete:',
                validate: validateIndexRemoval});
            
            // tryes perform the delete query
            try {
                await connection.query('DELETE FROM routes WHERE id = ?', [routeId]);
                console.log(`Route with ID ${routeId} delete successfully.`);
            } 
            //if there is an error print message
            catch (err) {
                console.error('Error delete route:', err);
            } 
            //finally bring program to an end
            finally {
                connection.end();
                process.exit(0);
            }
        } else {
            console.log('Access denied. Admins only.');
        }
    });

export default deleteRouteCommand;