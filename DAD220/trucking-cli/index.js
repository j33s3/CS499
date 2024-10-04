import dotenv from 'dotenv';
dotenv.config();

import { Command } from 'commander';
import { createConnection } from './config/dbConfig.js'

const program = new Command();

import viewRoutesCommand from './src/commands/viewRoutes.js';
import deleteRouteCommand from './src/commands/deleteRoute.js';
import addRouteCommand from './src/commands/addRoute.js';
import searchRoutesCommand from './src/commands/searchRoute.js';

program.addCommand(addRouteCommand);
program.addCommand(viewRoutesCommand);
program.addCommand(deleteRouteCommand);
program.addCommand(searchRoutesCommand);


(async () => {
    try {
        const connection = await createConnection();

        console.log('Connected to MySQL');

        process.on('SIGINT', async () => {
            try {
                await connection.end();
                console.log('MySQL connection closed.');
                process.exit();
            } catch (err) {
                console.error('Error closing MySQL connection:', err);
                process.exit(1);
            }
        });
    } catch (err) {
        console.error('Error connecting to MySQL', err);
        process.exit(1);
    } finally {
        await connection.end();
    }
    process.exit(0);
});

program.parse(process.argv);