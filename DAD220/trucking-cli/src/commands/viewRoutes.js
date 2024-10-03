import { Command } from'commander';
import { input } from'@inquirer/prompts';
import { createConnection } from'../../config/dbConfig.js';


const viewRoutesCommand = new Command('view-routes');

viewRoutesCommand
    .description('View all trucking routes (Admin only)')
    .action(async () => {
        const connection = await createConnection();

        const role  = await input({ message: 'Enter your role (user/Admin):' });

        if (role.toLowerCase() === 'admin') {
            try {

                const [results] = await connection.query('SELECT * FROM routes');

                console.table(results);
                await connection.end(); // Close the connection
            } catch (err) {
                console.error('Error retrieving routes:', err);
            }
        } else {
            console.log('Access denied. Admins only.');
        }
    });

export default viewRoutesCommand; // Exporting the command
