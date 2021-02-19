const NodeGdigrab = require("../dist/binding.js");
const assert = require("assert");

assert(NodeGdigrab, "The expected module is undefined");

function testBasic()
{
    const instance = new NodeGdigrab("mr-yeoman");
    //console.log(instance.greet())
    assert(instance.greet, "The expected method is not defined");
    assert.strictEqual(instance.greet("kermit"), "mr-yeoman", "Unexpected value returned");
    
    console.log(instance.grab())
    console.log(instance.grab())
}

function testInvalidParams()
{
    const instance = new NodeGdigrab();
}

assert.doesNotThrow(testBasic, undefined, "testBasic threw an expection");
assert.throws(testInvalidParams, undefined, "testInvalidParams didn't throw");

console.log("Tests passed- everything looks OK!");