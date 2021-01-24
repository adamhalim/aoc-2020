const fs = require('fs');
const input = fs.readFileSync('input.txt').toString().split('\n');


let allergenMap = new Map();
let ingredientMap = new Map();
input.forEach((line) => {
    // Index 0: all ingredients
    // Index 1: All allergens
    let splitLine = line.split(" (contains ");

    let ingredients = splitLine[0].split(" ");
    let allergens = splitLine[1].slice(0, -1).split(", ");

    allergens.forEach((allergen) => {
        if (allergenMap.has(allergen)) {
            allergenMap.get(allergen).push(ingredients);
        } else {
            let value = [ingredients];
            allergenMap.set(allergen, value);
        }
    });

    ingredients.forEach((ingredient) => {
        if (ingredientMap.has(ingredient)) {
            let value = ingredientMap.get(ingredient);
            ingredientMap.set(ingredient, ++value);
        } else {
            ingredientMap.set(ingredient, 1);
        }
    })
});

let allergens = [];

// For part 2:

let ingredsWithAllergens = [];

allergenMap.forEach((value, key) => {

    let firstVal = value[0];
    for (let i = 1; i < value.length; i++) {
        let t = firstVal.filter(x => value[i].includes(x));
        firstVal = t;
    }
    firstVal.forEach((val) => {
        if (!allergens.includes(val))
            allergens.push(val)
    });
    ingredsWithAllergens.push([key, firstVal]);
});

let count = 0;
ingredientMap.forEach((counter, ingredient) => {
    if (!allergens.includes(ingredient)) {
        count += ingredientMap.get(ingredient);
    }
});


console.log('Part one answer: ' + count)
let canonicalList = []; // our answer

for(let i = 0; i < ingredsWithAllergens.length; i++) {
    let value = ingredsWithAllergens[i];
    let ingredient = '';

    if(value[1].length === 1) {
        // Now we have found the allergen with only 1 ingredient
        ingredient = value[1];
        canonicalList.push([value[0], ingredient[0] ]);
        for(let j = 0; j < ingredsWithAllergens.length; j++) {
            if(j != i){
                ingredsWithAllergens[j][1] = ingredsWithAllergens[j][1].filter(item => item != ingredient);
            }
        }
        ingredsWithAllergens = ingredsWithAllergens.filter(tuple => tuple != value);
        i = -1;
    }
}

// Sort the list alphabetically on allergen
canonicalList.sort((a, b) => {
    if (a < b) {
        return -1;
    }
    if (a > b) {
        return 1;
    }
    return 0;
});

let ans = '';
canonicalList.forEach((value) => {
    ans += value[1] + ','
});
ans = ans.substr(0, ans.length -1);

console.log('Part two answer:\n' + ans);
