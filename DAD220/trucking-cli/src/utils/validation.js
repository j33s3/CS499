export function validateDriverName(name) {
    if(!name || name.length < 2) {
        return 'Driver name must be at least 2 characters long.';
    }
    return true;
};

export function validateTruckYear(year) {
    const currentYear = new Date.getFullYear();
    if(isNaN(year) || year < 1900 || year > currentYear) {
        return `Truck year must be between 1900 and ${currentYear}`
    }
    return true;
}