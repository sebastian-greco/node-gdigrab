const NodeGdigrab = require("../dist/binding.js");
const assert = require("assert");

assert(NodeGdigrab, "The expected module is undefined");

function testBasic()
{
    const instance = new NodeGdigrab("mr-yeoman");
    //console.log(instance.greet())
    assert(instance.greet, "The expected method is not defined");
    //assert.strictEqual(instance.greet("kermit"), "mr-yeoman", "Unexpected value returned");
    
    const start = Date.now();
    const amount = 1500;
    for (let i = amount; i > 0; i--) {
        ((instance).grab());
    }
    const took = Date.now() - start;
    console.log(`Took ${took} ms -  AVG ${took/amount}`)
}

function testInvalidParams()
{
    const instance = new NodeGdigrab();
}

assert.doesNotThrow(testBasic, undefined, "testBasic threw an expection");
//assert.throws(testInvalidParams, undefined, "testInvalidParams didn't throw");

console.log("Tests passed- everything looks OK!");