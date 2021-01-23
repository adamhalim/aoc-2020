const fs = require('fs');
const input = fs.readFileSync('input.txt').toString().split('\n');


let allergenMap = new Map();
let ingredientMap = new Map();
input.forEach((line) =>  {
    // Index 0: all ingredients
    // Index 1: All allergens
    let splitLine = line.split(" (contains ");

    let ingredients = splitLine[0].split(" ");
    let allergens = splitLine[1].slice(0,-1).split(", ");

    allergens.forEach((allergen) => {
        if(allergenMap.has(allergen)) {
             allergenMap.get(allergen).push(ingredients);
        } else {
            let value = [ingredients];
            allergenMap.set(allergen, value);
        }
    });

    ingredients.forEach((ingredient) => {
        if(ingredientMap.has(ingredient)) {
            let value = ingredientMap.get(ingredient);
            ingredientMap.set(ingredient, ++value);
        } else {
            ingredientMap.set(ingredient, 1);
        }
    })
});

let allergens = [];

allergenMap.forEach((value) => {

    let firstVal = value[0];
    for(let i = 1; i < value.length; i++ ) {
        let t = firstVal.filter(x => value[i].includes(x));
        firstVal = t;
    }
    firstVal.forEach((val) => { 
        if (!allergens.includes(val)) 
            allergens.push(val)
        });
});

let count = 0;
ingredientMap.forEach((counter, ingredient) => {
    if(!allergens.includes(ingredient)) {
        count += ingredientMap.get(ingredient);
    }
});



console.log(count)