import axios from 'axios';


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
    const listModels = ['VOLVO', 'FREIGHTLINER', 'KENWORTH', 'PETERBILT', 'INTERNATIONAL', 'WESTERN STAR', 'MACK', 'SCANIA', 'MAN', 'IVECO', 'STERLING', 'ISUZU'];
    if (!listModels.includes(make.toUpperCase())){
        return 'Truck manufacturer is not valid.';
    }
    return true;
}

export function validateTruckYear(year) {
    const currentYear = new Date().getFullYear();
    if(isNaN(year) || year < 1900 || year > (currentYear + 1)) {
        return `Truck year must be between 1900 and ${currentYear + 1}`
    }
    return true;
}

export async function validateStartingZIP(startZIP) {
    const url = `https://api.zippopotam.us/us/${startZIP}`;

    try {
        const response = axios.get(url);
        const { places } = response.data;

        if (response.status !== 200) {
            return 'Zipcode is invalid';
        }

        const place = places[0];
        const city = place['place name'];
        const state = place['state abbreviation'];

        const fullAddress = `${city}, ${state} ${startZIP}`;

    } catch (error) {
        return ('Error or invalid zipcode', error.response?.status);
    }

    return fullAddress;

}

export async function validateFinalZIP(endZip, startZIP) {
    if(startZIP === endZip) {
        return 'Error: Start and End locations are the same';
    }

    const url = `https://api.zippopotam.us/us/${endZip}`;

    try {
        const response = axios.get(url);
        const { places } = response.data;

        if (response.status !== 200) {
            return 'Zipcode is invalid';
        }

        const place = places[0];
        const city = place['place name'];
        const state = place['state abbreviation'];

        const fullAddress = `${city}, ${state} ${endZIP}`;

    } catch (error) {
        return ('Error or invalid zipcode', error.response?.status);
    }

    return fullAddress;
}

