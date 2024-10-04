import { Command } from'commander';
import { input } from'@inquirer/prompts';
import { createConnection } from'../../config/dbConfig.js';
import { validateIndexRemoval } from '../utils/validation.js';

const deleteRouteCommand = new Command('delete-route');

deleteRouteCommand
    .description('Delete a route by ID (Admin only)')
    .action(async() => {
        const role = await input({ message: 'Enter your role (user/Admin):'});
        const connection = await createConnection();

        if (role.toLowerCase() === 'admin') {
            const routeId = await input({ 
                message: 'Enter the route ID to delete:',
                validate: validateIndexRemoval});
            
            try {
                await connection.query('DELETE FROM routes WHERE id = ?', [routeId]);
                console.log(`Route with ID ${routeId} delete successfully.`);
                await connection.end();
            } catch (err) {
                console.error('Error delete route:', err);
            } finally {
                connection.end();
                process.exit(0);
            }
        } else {
            console.log('Access denied. Admins only.');
        }
    });

export default deleteRouteCommand;