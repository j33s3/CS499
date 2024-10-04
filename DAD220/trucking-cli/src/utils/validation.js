import axios from 'axios';

export const listModels = ['VOLVO', 'FREIGHTLINER', 'KENWORTH', 'PETERBILT', 'INTERNATIONAL', 'WESTERN STAR', 'MACK', 'SCANIA', 'MAN', 'IVECO', 'STERLING', 'ISUZU'];

export async function validateDriverName(name) {
    const validChars = /^[A-Za-z\s\-]+$/;

    if(!name || name.length < 2) {
        return 'Driver name must be at least 2 characters long.';
    }
    if(!name.match(validChars)) {
        return 'A name cannot contain numbers or special characters';
    }
    const spaceCount = (name.match(/ /g) || []).length;
    if(spaceCount > 2) {
        return 'Driver name must be either first, first and last, or first middle and last';
    }

    return true;
};


export function validateTruckModel(model) {
    const validChars = /^[A-Za-z0-9\s\-]/;
    if(!model || model.lenth < 2 || model.length > 30) {
        return 'Truck Model must be at least 2 characters long and must not exceed 30 characters';
    }
    if(!model.match(validChars)) {
        return 'The model must not contain special characters';
    }
    return true;
}

export function validateTruckMake(make) {
    if (!listModels.includes(make.toUpperCase())){
        return 'Truck manufacturer is not valid.';
    }
    return true;
}

export function validateTruckYear(year) {
    const currentYear = new Date().getFullYear();
    if(isNaN(year) || year < 1900 || year > (currentYear + 1)) {
        return `Truck year must be between 1900 and ${currentYear + 1}`;
    }
    return true;
}

export async function validateStartingZIP(startZIP) {
    const url = `https://api.zippopotam.us/us/${startZIP}`;

    try {

        const response = await axios.get(url);

        if(response.status === 200 && response.data.places && response.data.places.length > 0) {
            return true;
        } else {
            return "invalid zipcode";
        }
        
    } catch (error) {
        return "invalid zipcode";
    }   
}

export async function validateFinalZIP(endZIP, startZIP) {
    const url = `https://api.zippopotam.us/us/${endZIP}`;
    if(startZIP === endZIP) {
        return 'Error: Start and End locations are the same';
    }

    try {

        const response = await axios.get(url);

        if(response.status === 200 && response.data.places && response.data.places.length > 0) {
            return true;
        } else {
            return "invalid zipcode";
        }

    } catch (error) {
        return "invalid zipcode";
    }
}


export async function validateIndexRemoval(index) {
    const validChars = /^[0-9]+$/;
    if(!index.match(validChars)){
        return 'Invalid index format';
    }
    return true;
}

export async function validateSearch(search) {
    const forbiddenChars = /['";\(\)\{\}\[\]\<\>\|&!~`\\\/@#\$%\^*\+=]|--/;

    if(forbiddenChars.test(search)) {
        return 'Invalid characters in the search'
    }
    return true;

}

