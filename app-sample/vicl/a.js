if(typeof(Number) != 'undefined') {
Number.prototype.compare = function (item)
{
        if(this < item) {
            return -1;
        }
        else if(this > item) {
            return 1;
        }
        else {
            return 0;
        }
    }
    
Number.prototype.compare__Self = function (item){
        if(this < item) {
            return -1;
        }
        else if(this > item) {
            return 1;
        }
        else {
            return 0;
        }
    }
    
Number.prototype.equals = function (right)
{
        return this == right;
    }
    
Number.prototype.equals__Self = function (right){
        return this == right;
    }
    
Number.prototype.toString__ = function ()
{
        return new String(this);
    }
    
Number.prototype.clone = function ()
{
        return this;
    }
    
Number.prototype.clone__ = function (){
        return this;
    }
    
Number.prototype.add__Self = function (right)
{
        return this + right;
    }

    
Number.prototype.println__ = function ()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = System.println__Number(clover2Stack[clover2StackIndex+-1]); clover2StackIndex -= 1; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}

}
class Bool {
constructor() {
this.num = null;
}
num__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].num; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
num__bool(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].num = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
constructor__bool(num)
{
        this.num = num;

        return this;
    }

    
initialize__bool(num)
{
        this.num = num;

        return this;
    }

    
toString__()
{
        if(self.num) {
            return "true";
        }
        else {
            return "false";
        }
    }

}
if(typeof(String) != 'undefined') {
String.prototype.toString__ = function ()
{
        return new String(this);
    }

    
String.prototype.match__regex = function (regex_)
{
        return regex_.test(this);
    }
    
String.prototype.clone = function ()
{
        return `${this}`;
    }

    
String.prototype.clone__ = function (){
        return `${this}`;
    }

    
String.prototype.equals = function (str)
{
        return this == str;
    }
    
String.prototype.equals__Self = function (str){
        return this == str;
    }
    
String.prototype.compare = function (right)
{
        if(this == right) {
            return 0;
        }
        else if(this < right) {
            return -1;
        }
        else {
            return 1;
        }
    }
    
String.prototype.compare__Self = function (right){
        if(this == right) {
            return 0;
        }
        else if(this < right) {
            return -1;
        }
        else {
            return 1;
        }
    }
    
String.prototype.add__Self = function (right)
{
        return this + right;
    }
    

}
class Lambda {
constructor() {
this.function_ = null;
this.lambda_ = null;
this.parentVarNum = null;
this.funcName = null;
this.numParams = null;
this.stackPoint = null;
this.lvar = null;
this.listener = null;
}
function___()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].function_; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
function___Function(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].function_ = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
lambda___()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].lambda_; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
lambda___bool(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].lambda_ = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
parentVarNum__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].parentVarNum; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
parentVarNum__Number(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].parentVarNum = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
funcName__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].funcName; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
funcName__String(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].funcName = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
numParams__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].numParams; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
numParams__Number(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].numParams = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
stackPoint__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].stackPoint; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
stackPoint__Number(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].stackPoint = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
lvar__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].lvar; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
lvar__Number(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].lvar = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
listener__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].listener; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
listener__bool(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].listener = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
constructor__Function_bool_Number_String_Number_Number(function_,lambda_,parent_var_num,func_name,num_params,lvar)
{
        this.function_ = function_;
        this.lambda_ = lambda_;
        this.parentVarNum = parent_var_num;
        this.funcName = func_name;
        this.numParams = num_params;
        this.lvar = lvar;
        this.listener = false;

        return this;
    }

    
copyParentStack(lvar)
{
        for(var i=0; i<this.parentVarNum; i++) { 
            clover2Stack[lvar+i] = clover2Stack[this.lvar+i];
        }
    }

    
copyParentStack__Number(lvar)
{
        for(var i=0; i<this.parentVarNum; i++) { 
            clover2Stack[lvar+i] = clover2Stack[this.lvar+i];
        }
    }

    
copyBackParentStack(lvar)
{
        for(var i=0; i<this.parentVarNum; i++) { 
            clover2Stack[this.lvar+i] = clover2Stack[lvar+i];
        }
    }

copyBackParentStack__Number(lvar)
{
        for(var i=0; i<this.parentVarNum; i++) { 
            clover2Stack[this.lvar+i] = clover2Stack[lvar+i];
        }
    }

}
if(typeof(Map) != 'undefined') {
Map.prototype.size__ = function ()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].size; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
Map.prototype.size__Number = function (value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].size = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
Map.prototype.get__GenericsParametorClass0 = function (key)
{
        for(var [key2, value] of this.entries()) {
            if(key2.equals(key)) {
                return value;
            }
        }

        return null;
    }

    
Map.prototype.delete__GenericsParametorClass0 = function (key)
{
        for(var [key2, value] of this.entries()) {
            if(key2.equals(key)) {
                this.delete(key);
                return true;
            }
        }

        return false;
    }

    
Map.prototype.has__GenericsParametorClass0 = function (key)
{
        for(var [key2, value] of this.entries()) {
            if(key2.equals(key)) {
                return true;
            }
        }

        return false;
    }

    
Map.prototype.forEach__lambda = function (block_)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 4
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].entries(); clover2StackIndex -= 1; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
clover2Stack[lvar+2] = clover2Stack[clover2StackIndex-1]
clover2StackIndex -= 1
while(true) {
clover2Stack[clover2StackIndex] = true; clover2StackIndex++
if(!clover2Stack[--clover2StackIndex]) { 
break;
}
clover2Stack[clover2StackIndex] = clover2Stack[lvar+2]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].next(); clover2StackIndex -= 1; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
clover2Stack[lvar+3] = clover2Stack[clover2StackIndex-1]
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].done; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2Stack[--clover2StackIndex]) { 
break;
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
clover2GlobalStack[clover2GlobalStackIndex] = clover2Stack[clover2StackIndex-1]; clover2GlobalStackIndex++; clover2StackIndex--;
}
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
clover2GlobalStack[clover2GlobalStackIndex] = clover2Stack[clover2StackIndex-1]; clover2GlobalStackIndex++; clover2StackIndex--;
clover2Stack[clover2StackIndex] = clover2GlobalStack[clover2GlobalStackIndex-1]; clover2StackIndex++; clover2GlobalStackIndex--
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2Stack[clover2StackIndex] = 0; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-2].items__Number(clover2Stack[clover2StackIndex+-1]); clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2Stack[clover2StackIndex] = 1; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-2].items__Number(clover2Stack[clover2StackIndex+-1]); clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
var params_top = clover2StackIndex-3
var lambda_object = clover2Stack[params_top]
var lambda_params = clover2Stack.slice(params_top+1, params_top+1+2)
var parent_var_num = lambda_object.parentVarNum;
if(!lambda_object.lambda_) { clover2StackIndex -= 2; clover2StackIndex += parent_var_num; }
if(!lambda_object.lambda_) { for(var i=0; i<lambda_params.length; i++) { clover2Stack[clover2StackIndex] = lambda_params[i]; clover2StackIndex++; } }
if(lambda_object.funcName == "") { tmp = lambda_object.function_(); } else { tmp = block_(); }
clover2StackIndex -= 3
if(!lambda_object.lambda_) { clover2StackIndex -= parent_var_num; }
clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
clover2StackIndex -= 1
}
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}

}
if(typeof(Set) != 'undefined') {
Set.prototype.size__ = function ()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].size; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
Set.prototype.size__Number = function (value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].size = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
Set.prototype.constructor = function (array)
{
        for(var i=0; i<array.length; i++) {
            this.add__GenericsParametorClass0(array[i]);
        }
        return this;
    }

    
Set.prototype.constructor__Array = function (array){
        for(var i=0; i<array.length; i++) {
            this.add__GenericsParametorClass0(array[i]);
        }
        return this;
    }

    
Set.prototype.add__GenericsParametorClass0 = function (value)
{
        var it = this.entries();

        var found = false;

        while(true) {
            var it_res = it.next();

            if(it_res.done) {
                break;
            }

            if(it_res.value[0].equals(value)) {
                found = true;
            }
        }

        if(!found) {
            this.add(value);
        }
        
        return this;
    }

    
Set.prototype.equals = function (right)
{
        if(this.size != right.size) {
            return false;
        }

        var it = this.entries();
        var it2 = right.entries();

        while(true) {
            var it_res = it.next();
            var it_res2 = it2.next();

            if(it_res.done) {
                break;
            }

            if(!it_res.value[0].equals(it_res2.value[0])) {
                return false;
            }
        }

        return true;
    }

    
Set.prototype.equals__Self = function (right){
        if(this.size != right.size) {
            return false;
        }

        var it = this.entries();
        var it2 = right.entries();

        while(true) {
            var it_res = it.next();
            var it_res2 = it2.next();

            if(it_res.done) {
                break;
            }

            if(!it_res.value[0].equals(it_res2.value[0])) {
                return false;
            }
        }

        return true;
    }

    
Set.prototype.forEach__lambda = function (block_)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 4
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].entries(); clover2StackIndex -= 1; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
clover2Stack[lvar+2] = clover2Stack[clover2StackIndex-1]
clover2StackIndex -= 1
while(true) {
clover2Stack[clover2StackIndex] = true; clover2StackIndex++
if(!clover2Stack[--clover2StackIndex]) { 
break;
}
clover2Stack[clover2StackIndex] = clover2Stack[lvar+2]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].next(); clover2StackIndex -= 1; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
clover2Stack[lvar+3] = clover2Stack[clover2StackIndex-1]
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].done; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2Stack[--clover2StackIndex]) { 
break;
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
clover2GlobalStack[clover2GlobalStackIndex] = clover2Stack[clover2StackIndex-1]; clover2GlobalStackIndex++; clover2StackIndex--;
}
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
clover2GlobalStack[clover2GlobalStackIndex] = clover2Stack[clover2StackIndex-1]; clover2GlobalStackIndex++; clover2StackIndex--;
clover2Stack[clover2StackIndex] = clover2GlobalStack[clover2GlobalStackIndex-1]; clover2StackIndex++; clover2GlobalStackIndex--
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2Stack[clover2StackIndex] = 0; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-2].items__Number(clover2Stack[clover2StackIndex+-1]); clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
var params_top = clover2StackIndex-2
var lambda_object = clover2Stack[params_top]
var lambda_params = clover2Stack.slice(params_top+1, params_top+1+1)
var parent_var_num = lambda_object.parentVarNum;
if(!lambda_object.lambda_) { clover2StackIndex -= 1; clover2StackIndex += parent_var_num; }
if(!lambda_object.lambda_) { for(var i=0; i<lambda_params.length; i++) { clover2Stack[clover2StackIndex] = lambda_params[i]; clover2StackIndex++; } }
if(lambda_object.funcName == "") { tmp = lambda_object.function_(); } else { tmp = block_(); }
clover2StackIndex -= 2
if(!lambda_object.lambda_) { clover2StackIndex -= parent_var_num; }
clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
clover2StackIndex -= 1
}
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}

}
class Tuple1 {
constructor() {
this.value1 = null;
}
value1__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value1; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value1__GenericsParametorClass0N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value1 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
initialize__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value1 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
initialize__GenericsParametorClass0(value1)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value1 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
clone()
{
        var result = new Tuple1();

        if(this.value1 != null) {
            result.value1 = this.value1.clone();
        }

        return result;
    }

    
clone__()
{
        var result = new Tuple1();

        if(this.value1 != null) {
            result.value1 = this.value1.clone();
        }

        return result;
    }

    
equals(right)
{
        return this.value1.equals(right.value1);
    }

    
equals__Self(right)
{
        return this.value1.equals(right.value1);
    }

    
toString__()
{
        return "tuple {" + this.value1.toString__() + "}";
    }

}
class Tuple2 {
constructor() {
this.value1 = null;
this.value2 = null;
}
value1__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value1; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value1__GenericsParametorClass0N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value1 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value2__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value2; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value2__GenericsParametorClass1N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value2 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
initialize__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value1 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value2 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
initialize__GenericsParametorClass0_GenericsParametorClass1(value1,value2)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-3
clover2StackIndex = lvar + 3
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value1 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+2]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value2 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+3
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+3;
return tmp;
}
clone()
{
        var result = new Tuple2();

        if(this.value1 != null) {
            result.value1 = this.value1.clone();
        }
        if(this.value2 != null) {
            result.value2 = this.value2.clone();
        }

        return result;
    }

    
clone__()
{
        var result = new Tuple2();

        if(this.value1 != null) {
            result.value1 = this.value1.clone();
        }
        if(this.value2 != null) {
            result.value2 = this.value2.clone();
        }

        return result;
    }

    
equals(right)
{
        return this.value1.equals(right.value1) && this.value2.equals(right.value2);
    }

    
equals__Self(right)
{
        return this.value1.equals(right.value1) && this.value2.equals(right.value2);
    }

    
toString__()
{
        return "tuple {" + this.value1.toString__() + "," + this.value2.toString__() + "}";
    }

}
class Tuple3 {
constructor() {
this.value1 = null;
this.value2 = null;
this.value3 = null;
}
value1__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value1; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value1__GenericsParametorClass0N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value1 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value2__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value2; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value2__GenericsParametorClass1N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value2 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value3__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value3; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value3__GenericsParametorClass2N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value3 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
initialize__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value1 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value2 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value3 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
initialize__GenericsParametorClass0_GenericsParametorClass1_GenericsParametorClass2(value1,value2,value3)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-4
clover2StackIndex = lvar + 4
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value1 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+2]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value2 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value3 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+4
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+4;
return tmp;
}
clone()
{
        var result = new Tuple3();

        if(this.value1 != null) {
            result.value1 = this.value1.clone();
        }
        if(this.value2 != null) {
            result.value2 = this.value2.clone();
        }
        if(this.value3 != null) {
            result.value3 = this.value3.clone();
        }

        return result;
    }

    
clone__()
{
        var result = new Tuple3();

        if(this.value1 != null) {
            result.value1 = this.value1.clone();
        }
        if(this.value2 != null) {
            result.value2 = this.value2.clone();
        }
        if(this.value3 != null) {
            result.value3 = this.value3.clone();
        }

        return result;
    }

    
equals(right)
{
        return this.value1.equals(right.value1) && this.value2.equals(right.value2) && this.value3.equals(right.value3);
    }

    
equals__Self(right)
{
        return this.value1.equals(right.value1) && this.value2.equals(right.value2) && this.value3.equals(right.value3);
    }

    
toString__()
{
        return "tuple {" + this.value1.toString__() + "," + this.value2.toString__() + "," + this.value3.toString__() + "}";
    }

}
class Tuple4 {
constructor() {
this.value1 = null;
this.value2 = null;
this.value3 = null;
this.value4 = null;
}
value1__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value1; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value1__GenericsParametorClass0N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value1 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value2__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value2; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value2__GenericsParametorClass1N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value2 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value3__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value3; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value3__GenericsParametorClass2N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value3 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value4__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value4; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value4__GenericsParametorClass3N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value4 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
initialize__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value1 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value2 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value3 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value4 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
initialize__GenericsParametorClass0_GenericsParametorClass1_GenericsParametorClass2_GenericsParametorClass3(value1,value2,value3,value4)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-5
clover2StackIndex = lvar + 5
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value1 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+2]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value2 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value3 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+4]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value4 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+5
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+5;
return tmp;
}
clone()
{
        var result = new Tuple4();

        if(this.value1 != null) {
            result.value1 = this.value1.clone();
        }
        if(this.value2 != null) {
            result.value2 = this.value2.clone();
        }
        if(this.value3 != null) {
            result.value3 = this.value3.clone();
        }
        if(this.value4 != null) {
            result.value4 = this.value4.clone();
        }

        return result;
    }

    
clone__()
{
        var result = new Tuple4();

        if(this.value1 != null) {
            result.value1 = this.value1.clone();
        }
        if(this.value2 != null) {
            result.value2 = this.value2.clone();
        }
        if(this.value3 != null) {
            result.value3 = this.value3.clone();
        }
        if(this.value4 != null) {
            result.value4 = this.value4.clone();
        }

        return result;
    }

    
equals(right)
{
        return this.value1.equals(right.value1) && this.value2.equals(right.value2) && this.value3.equals(right.value3) && this.value4.equals(right.value4);
    }

    
equals__Self(right)
{
        return this.value1.equals(right.value1) && this.value2.equals(right.value2) && this.value3.equals(right.value3) && this.value4.equals(right.value4);
    }

    
toString__()
{
        return "tuple {" + this.value1.toString__() + "," + this.value2.toString__() + "," + this.value3.toString__() + "," + this.value4.toString__() + "}";
    }

}
class Tuple5 {
constructor() {
this.value1 = null;
this.value2 = null;
this.value3 = null;
this.value4 = null;
this.value5 = null;
}
value1__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value1; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value1__GenericsParametorClass0N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value1 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value2__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value2; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value2__GenericsParametorClass1N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value2 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value3__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value3; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value3__GenericsParametorClass2N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value3 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value4__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value4; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value4__GenericsParametorClass3N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value4 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value5__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value5; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value5__GenericsParametorClass4N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value5 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
initialize__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value1 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value2 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value3 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value4 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value5 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
initialize__GenericsParametorClass0_GenericsParametorClass1_GenericsParametorClass2_GenericsParametorClass3_GenericsParametorClass4(value1,value2,value3,value4,value5)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-6
clover2StackIndex = lvar + 6
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value1 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+2]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value2 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value3 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+4]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value4 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+5]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value5 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+6
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+6;
return tmp;
}
clone()
{
        var result = new Tuple5();

        if(this.value1 != null) {
            result.value1 = this.value1.clone();
        }
        if(this.value2 != null) {
            result.value2 = this.value2.clone();
        }
        if(this.value3 != null) {
            result.value3 = this.value3.clone();
        }
        if(this.value4 != null) {
            result.value4 = this.value4.clone();
        }
        if(this.value5 != null) {
            result.value5 = this.value5.clone();
        }

        return result;
    }

    
clone__()
{
        var result = new Tuple5();

        if(this.value1 != null) {
            result.value1 = this.value1.clone();
        }
        if(this.value2 != null) {
            result.value2 = this.value2.clone();
        }
        if(this.value3 != null) {
            result.value3 = this.value3.clone();
        }
        if(this.value4 != null) {
            result.value4 = this.value4.clone();
        }
        if(this.value5 != null) {
            result.value5 = this.value5.clone();
        }

        return result;
    }

    
equals(right)
{
        return this.value1.equals(right.value1) && this.value2.equals(right.value2) && this.value3.equals(right.value3) && this.value4.equals(right.value4) && this.value5.equals(right.value5);
    }

    
equals__Self(right)
{
        return this.value1.equals(right.value1) && this.value2.equals(right.value2) && this.value3.equals(right.value3) && this.value4.equals(right.value4) && this.value5.equals(right.value5);
    }

    
toString__()
{
        return "tuple {" + this.value1.toString__() + ","+ this.value2.toString__() + "," + this.value3.toString__() + "," + this.value4.toString__() + "," + this.value5.toString__() + "}";
    }

}
class Tuple6 {
constructor() {
this.value1 = null;
this.value2 = null;
this.value3 = null;
this.value4 = null;
this.value5 = null;
this.value6 = null;
}
value1__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value1; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value1__GenericsParametorClass0N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value1 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value2__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value2; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value2__GenericsParametorClass1N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value2 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value3__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value3; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value3__GenericsParametorClass2N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value3 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value4__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value4; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value4__GenericsParametorClass3N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value4 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value5__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value5; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value5__GenericsParametorClass4N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value5 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value6__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value6; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value6__GenericsParametorClass5N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value6 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
initialize__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value1 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value2 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value3 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value4 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value5 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value6 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
initialize__GenericsParametorClass0_GenericsParametorClass1_GenericsParametorClass2_GenericsParametorClass3_GenericsParametorClass4_GenericsParametorClass5(value1,value2,value3,value4,value5,value6)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-7
clover2StackIndex = lvar + 7
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value1 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+2]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value2 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value3 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+4]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value4 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+5]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value5 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+6]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value6 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+7
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+7;
return tmp;
}
clone()
{
        var result = new Tuple6();

        if(this.value1 != null) {
            result.value1 = this.value1.clone();
        }
        if(this.value2 != null) {
            result.value2 = this.value2.clone();
        }
        if(this.value3 != null) {
            result.value3 = this.value3.clone();
        }
        if(this.value4 != null) {
            result.value4 = this.value4.clone();
        }
        if(this.value5 != null) {
            result.value5 = this.value5.clone();
        }
        if(this.value6 != null) {
            result.value6 = this.value6.clone();
        }

        return result;
    }

    
clone__()
{
        var result = new Tuple6();

        if(this.value1 != null) {
            result.value1 = this.value1.clone();
        }
        if(this.value2 != null) {
            result.value2 = this.value2.clone();
        }
        if(this.value3 != null) {
            result.value3 = this.value3.clone();
        }
        if(this.value4 != null) {
            result.value4 = this.value4.clone();
        }
        if(this.value5 != null) {
            result.value5 = this.value5.clone();
        }
        if(this.value6 != null) {
            result.value6 = this.value6.clone();
        }

        return result;
    }

    
equals(right)
{
        return this.value1.equals(right.value1) && this.value2.equals(right.value2) && this.value3.equals(right.value3) && this.value4.equals(right.value4) && this.value5.equals(right.value5) && this.value6.equals(right.value6);
    }

    
equals__Self(right)
{
        return this.value1.equals(right.value1) && this.value2.equals(right.value2) && this.value3.equals(right.value3) && this.value4.equals(right.value4) && this.value5.equals(right.value5) && this.value6.equals(right.value6);
    }

    
toString__()
{
        return "tuple {" + this.value1.toString__() + "," + this.value2.toString__() + "," + this.value3.toString__() + "," + this.value4.toString__() + "," + this.value5.toString__() + "," + this.value6.toString__() + "}";
    }

}
class Tuple7 {
constructor() {
this.value1 = null;
this.value2 = null;
this.value3 = null;
this.value4 = null;
this.value5 = null;
this.value6 = null;
this.value7 = null;
}
value1__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value1; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value1__GenericsParametorClass0N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value1 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value2__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value2; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value2__GenericsParametorClass1N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value2 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value3__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value3; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value3__GenericsParametorClass2N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value3 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value4__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value4; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value4__GenericsParametorClass3N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value4 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value5__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value5; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value5__GenericsParametorClass4N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value5 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value6__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value6; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value6__GenericsParametorClass5N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value6 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value7__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value7; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value7__GenericsParametorClass6N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value7 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
initialize__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value1 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value2 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value3 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value4 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value5 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value6 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value7 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
initialize__GenericsParametorClass0_GenericsParametorClass1_GenericsParametorClass2_GenericsParametorClass3_GenericsParametorClass4_GenericsParametorClass5_GenericsParametorClass6(value1,value2,value3,value4,value5,value6,value7)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-8
clover2StackIndex = lvar + 8
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value1 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+2]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value2 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value3 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+4]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value4 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+5]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value5 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+6]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value6 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+7]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value7 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+8
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+8;
return tmp;
}
clone()
{
        var result = new Tuple7();

        if(this.value1 != null) {
            result.value1 = this.value1.clone();
        }
        if(this.value2 != null) {
            result.value2 = this.value2.clone();
        }
        if(this.value3 != null) {
            result.value3 = this.value3.clone();
        }
        if(this.value4 != null) {
            result.value4 = this.value4.clone();
        }
        if(this.value5 != null) {
            result.value5 = this.value5.clone();
        }
        if(this.value6 != null) {
            result.value6 = this.value6.clone();
        }
        if(this.value7 != null) {
            result.value7 = this.value7.clone();
        }

        return result;
    }

    
clone__()
{
        var result = new Tuple7();

        if(this.value1 != null) {
            result.value1 = this.value1.clone();
        }
        if(this.value2 != null) {
            result.value2 = this.value2.clone();
        }
        if(this.value3 != null) {
            result.value3 = this.value3.clone();
        }
        if(this.value4 != null) {
            result.value4 = this.value4.clone();
        }
        if(this.value5 != null) {
            result.value5 = this.value5.clone();
        }
        if(this.value6 != null) {
            result.value6 = this.value6.clone();
        }
        if(this.value7 != null) {
            result.value7 = this.value7.clone();
        }

        return result;
    }

    
equals(right)
{
        return this.value1.equals(right.value1) && this.value2.equals(right.value2) && this.value3.equals(right.value3) && this.value4.equals(right.value4) && this.value5.equals(right.value5) && this.value6.equals(right.value6) && this.value7.equals(right.value7);
    }

    
equals__Self(right)
{
        return this.value1.equals(right.value1) && this.value2.equals(right.value2) && this.value3.equals(right.value3) && this.value4.equals(right.value4) && this.value5.equals(right.value5) && this.value6.equals(right.value6) && this.value7.equals(right.value7);
    }

    
toString__()
{
        return "tuple {" + this.value1.toString__() + "," + this.value2.toString__() + "," + this.value3.toString__() + "," + this.value4.toString__() + "," + this.value5.toString__() + "," + this.value6.toString__() + "," + this.value7.toString__() + "}";
    }

}
class Tuple8 {
constructor() {
this.value1 = null;
this.value2 = null;
this.value3 = null;
this.value4 = null;
this.value5 = null;
this.value6 = null;
this.value7 = null;
this.value8 = null;
}
value1__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value1; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value1__GenericsParametorClass0N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value1 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value2__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value2; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value2__GenericsParametorClass1N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value2 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value3__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value3; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value3__GenericsParametorClass2N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value3 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value4__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value4; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value4__GenericsParametorClass3N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value4 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value5__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value5; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value5__GenericsParametorClass4N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value5 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value6__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value6; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value6__GenericsParametorClass5N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value6 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value7__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value7; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value7__GenericsParametorClass6N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value7 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value8__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value8; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value8__GenericsParametorClass7N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value8 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
initialize__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value1 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value2 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value3 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value4 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value5 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value6 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value7 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value8 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
initialize__GenericsParametorClass0_GenericsParametorClass1_GenericsParametorClass2_GenericsParametorClass3_GenericsParametorClass4_GenericsParametorClass5_GenericsParametorClass6_GenericsParametorClass7(value1,value2,value3,value4,value5,value6,value7,value8)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-9
clover2StackIndex = lvar + 9
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value1 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+2]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value2 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value3 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+4]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value4 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+5]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value5 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+6]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value6 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+7]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value7 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+8]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value8 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+9
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+9;
return tmp;
}
clone()
{
        var result = new Tuple8();

        if(this.value1 != null) {
            result.value1 = this.value1.clone();
        }
        if(this.value2 != null) {
            result.value2 = this.value2.clone();
        }
        if(this.value3 != null) {
            result.value3 = this.value3.clone();
        }
        if(this.value4 != null) {
            result.value4 = this.value4.clone();
        }
        if(this.value5 != null) {
            result.value5 = this.value5.clone();
        }
        if(this.value6 != null) {
            result.value6 = this.value6.clone();
        }
        if(this.value7 != null) {
            result.value7 = this.value7.clone();
        }
        if(this.value8 != null) {
            result.value8 = this.value8.clone();
        }

        return result;
    }

    
clone__()
{
        var result = new Tuple8();

        if(this.value1 != null) {
            result.value1 = this.value1.clone();
        }
        if(this.value2 != null) {
            result.value2 = this.value2.clone();
        }
        if(this.value3 != null) {
            result.value3 = this.value3.clone();
        }
        if(this.value4 != null) {
            result.value4 = this.value4.clone();
        }
        if(this.value5 != null) {
            result.value5 = this.value5.clone();
        }
        if(this.value6 != null) {
            result.value6 = this.value6.clone();
        }
        if(this.value7 != null) {
            result.value7 = this.value7.clone();
        }
        if(this.value8 != null) {
            result.value8 = this.value8.clone();
        }

        return result;
    }

    
equals(right)
{
        return this.value1.equals(right.value1) && this.value2.equals(right.value2) && this.value3.equals(right.value3) && this.value4.equals(right.value4) && this.value5.equals(right.value5) && this.value6.equals(right.value6) && this.value7.equals(right.value7) && this.value8.equals(right.value8);
    }

    
equals__Self(right)
{
        return this.value1.equals(right.value1) && this.value2.equals(right.value2) && this.value3.equals(right.value3) && this.value4.equals(right.value4) && this.value5.equals(right.value5) && this.value6.equals(right.value6) && this.value7.equals(right.value7) && this.value8.equals(right.value8);
    }

    
toString__()
{
        return "tuple {" + this.value1.toString__() + "," + this.value2.toString__() + ","+ this.value3.toString__() + "," + this.value4.toString__() + ","+ this.value5.toString__() + "," + this.value6.toString__() + "," + this.value7.toString__() + "," + this.value8.toString__() + "}";
    }

}
class Tuple9 {
constructor() {
this.value1 = null;
this.value2 = null;
this.value3 = null;
this.value4 = null;
this.value5 = null;
this.value6 = null;
this.value7 = null;
this.value8 = null;
this.value9 = null;
}
value1__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value1; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value1__GenericsParametorClass0N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value1 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value2__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value2; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value2__GenericsParametorClass1N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value2 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value3__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value3; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value3__GenericsParametorClass2N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value3 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value4__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value4; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value4__GenericsParametorClass3N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value4 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value5__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value5; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value5__GenericsParametorClass4N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value5 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value6__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value6; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value6__GenericsParametorClass5N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value6 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value7__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value7; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value7__GenericsParametorClass6N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value7 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value8__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value8; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value8__GenericsParametorClass7N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value8 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
value9__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].value9; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
value9__GenericsParametorClass8N(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value9 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
initialize__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value1 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value2 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value3 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value4 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value5 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value6 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value7 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value8 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value9 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
initialize__GenericsParametorClass0_GenericsParametorClass1_GenericsParametorClass2_GenericsParametorClass3_GenericsParametorClass4_GenericsParametorClass5_GenericsParametorClass6_GenericsParametorClass7_GenericsParametorClass8(value1,value2,value3,value4,value5,value6,value7,value8,value9)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-10
clover2StackIndex = lvar + 10
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value1 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+2]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value2 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value3 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+4]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value4 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+5]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value5 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+6]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value6 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+7]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value7 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+8]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value8 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+9]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].value9 = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+10
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+10;
return tmp;
}
clone()
{
        var result = Tuple9();

        if(this.value1 != null) {
            result.value1 = this.value1.clone();
        }
        if(this.value2 != null) {
            result.value2 = this.value2.clone();
        }
        if(this.value3 != null) {
            result.value3 = this.value3.clone();
        }
        if(this.value4 != null) {
            result.value4 = this.value4.clone();
        }
        if(this.value5 != null) {
            result.value5 = this.value5.clone();
        }
        if(this.value6 != null) {
            result.value6 = this.value6.clone();
        }
        if(this.value7 != null) {
            result.value7 = this.value7.clone();
        }
        if(this.value8 != null) {
            result.value8 = this.value8.clone();
        }
        if(this.value9 != null) {
            result.value9 = this.value9.clone();
        }

        return result;
    }

    
clone__()
{
        var result = Tuple9();

        if(this.value1 != null) {
            result.value1 = this.value1.clone();
        }
        if(this.value2 != null) {
            result.value2 = this.value2.clone();
        }
        if(this.value3 != null) {
            result.value3 = this.value3.clone();
        }
        if(this.value4 != null) {
            result.value4 = this.value4.clone();
        }
        if(this.value5 != null) {
            result.value5 = this.value5.clone();
        }
        if(this.value6 != null) {
            result.value6 = this.value6.clone();
        }
        if(this.value7 != null) {
            result.value7 = this.value7.clone();
        }
        if(this.value8 != null) {
            result.value8 = this.value8.clone();
        }
        if(this.value9 != null) {
            result.value9 = this.value9.clone();
        }

        return result;
    }

    
equals(right)
{
        return this.value1.equals(right.value1) && this.value2.equals(right.value2) && this.value3.equals(right.value3) && this.value4.equals(right.value4) && this.value5.equals(right.value5) && this.value6.equals(right.value6) && this.value7.equals(right.value7) && this.value8.equals(right.value8) && this.value9.equals(right.value9);
    }

    
equals__Self(right)
{
        return this.value1.equals(right.value1) && this.value2.equals(right.value2) && this.value3.equals(right.value3) && this.value4.equals(right.value4) && this.value5.equals(right.value5) && this.value6.equals(right.value6) && this.value7.equals(right.value7) && this.value8.equals(right.value8) && this.value9.equals(right.value9);
    }

    
toString__()
{
        return "tuple {" + this.value1.toString__() + "," + this.value2.toString__() + "," + this.value3.toString__() + "," + this.value4.toString__() + "," + this.value5.toString__() + "," + this.value6.toString__() + "," + this.value7.toString__() + "," + this.value8.toString__() + "," + this.value9.toString__() + "}";
    }

}
class System {
constructor() {
}
static println__Anonymous(obj)
{
        console.log(obj);
    }
    
static println__String(str)
{
        console.log(str);
    }
    
static print__String(str)
{
        process.stdout.write(str);
    }
    
static println__Number(num)
{
        console.log(num);
    }
    
static typeOf__Anonymous(obj)
{
        return typeOf(obj);
    }
    
static typeOfNativeObject__Anonymous(obj)
{
        return typeOfNativeObject(obj);
    }
    
static assert__bool(exp)
{
        console.assert(exp);
    }

    
static alert__Anonymous(obj)
{
        alert(obj);
    }

    
static initialize__()
{
        if(typeof document !== 'undefined') {
            System.document = document;
        }
    }

}
System.document = null;
System.initialize__();
class Clover {
constructor() {
}
static test__String_bool(str,exp)
{
        process.stdout.write(str + "...");
        console.log(exp);
        console.assert(exp);
    }

}
class Exception {
constructor() {
this.message = null;
}
message__()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].message; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
message__String(value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].message = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
initialize__String(message)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].message = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
}
if(typeof(Array) != 'undefined') {
Array.prototype.length__ = function ()
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].length; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
}
Array.prototype.length__Number = function (value)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 2
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].length = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
Array.prototype.items__Number = function (n)
{
        return this[n];
    }
    
Array.prototype.includes__GenericsParametorClass0 = function (item)
{
        for(var i=0; i<this.length; i++) {
            if(this[i].equals(item)) {
                return true;
            }
        }

        return false;
    }
    
Array.prototype.copyWithin__Number_Number = function (index,start)
{
        var end = this.length;
        this.copyWithin(index, start, end);

        return this;
    }
    
Array.prototype.copyWithin__Number_Number_Number = function (index,start,end)
{
        this.copyWithin(index, start, end);

        return this;
    }
    
Array.prototype.fill__GenericsParametorClass0_Number = function (data,start)
{
        var end = this.length;
        this.fill(data, start, end);

        return this;
    }
    
Array.prototype.fill__GenericsParametorClass0_Number_Number = function (data,start,end)
{
        this.fill(data, start, end);

        return this;
    }

    
Array.prototype.equals = function (array_)
{
        if(this.length == array_.length) {
            for(var i=0; i<this.length; i++) {
                if(!this[i].equals(array_[i])) {
                    return false;
                }
            }

            return true;
        }
        else {
            return false;
        }
    }

    
Array.prototype.equals__Self = function (array_){
        if(this.length == array_.length) {
            for(var i=0; i<this.length; i++) {
                if(!this[i].equals(array_[i])) {
                    return false;
                }
            }

            return true;
        }
        else {
            return false;
        }
    }

    
Array.prototype.replace__Number_GenericsParametorClass0 = function (n,item)
{
        var item = this[n];
        this[n] = item;
        return item;
    }

    
Array.prototype.toString__ = function ()
{
        var result = "Array {";

        for(var i= 0; i<this.length; i++) {
            result = result + this[i].toString__();

            if(i < this.length-1) {
                result = result + ",";
            }
        }
        
        result = result + "}";

        return result;
    }

    
Array.prototype.quickSort = function (left,right,fun)
{
        var l_hold = left;
        var r_hold = right;

        var pivot = this[left];
        var pivot_num = left;

        while(left < right) {
            while((fun(this[right], pivot) >= 0) && (left < right)) {
                right--;
            }

            if(left != right) {
                this[left] = this[right];
                left++;
            }

            while((fun(this[left], pivot) <= 0) && (left < right)) {
                left++;
            }

            if(left != right) {
                this[right] = this[left];
                right--;
            }
        }

        this[left] = pivot;

        pivot_num = left;

        var left2 = l_hold;
        var right2 = r_hold;

        if(left2 < pivot_num) {
            this.quickSort(left2, pivot_num-1, fun);
        }

        if(right2 > pivot_num) {
            this.quickSort(pivot_num+1, right2, fun);
        }

        return this;
    }

    
Array.prototype.quickSort__Number_Number_lambda = function (left,right,fun){
        var l_hold = left;
        var r_hold = right;

        var pivot = this[left];
        var pivot_num = left;

        while(left < right) {
            while((fun(this[right], pivot) >= 0) && (left < right)) {
                right--;
            }

            if(left != right) {
                this[left] = this[right];
                left++;
            }

            while((fun(this[left], pivot) <= 0) && (left < right)) {
                left++;
            }

            if(left != right) {
                this[right] = this[left];
                right--;
            }
        }

        this[left] = pivot;

        pivot_num = left;

        var left2 = l_hold;
        var right2 = r_hold;

        if(left2 < pivot_num) {
            this.quickSort(left2, pivot_num-1, fun);
        }

        if(right2 > pivot_num) {
            this.quickSort(pivot_num+1, right2, fun);
        }

        return this;
    }

    
Array.prototype.sort__ = function ()
{
        if(this.length > 0) {
            return this.quickSort(0, this.length-1, function(left, right) { return left.compare(right); });
        }
    }

    
Array.prototype.sort__lambda = function (fun)
{
        if(this.length > 0) {
            return this.quickSort(0, this.length-1, fun.function_);
        }
    }

    
Array.prototype.every__lambda = function (block_)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 4
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].length; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2Stack[lvar+2] = clover2Stack[clover2StackIndex-1]
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = 0; clover2StackIndex++
clover2Stack[lvar+3] = clover2Stack[clover2StackIndex-1]
clover2StackIndex -= 1
while(true) {
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+2]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-2] < clover2Stack[clover2StackIndex-1]; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
if(!clover2Stack[--clover2StackIndex]) { 
break;
}
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-2].items__Number(clover2Stack[clover2StackIndex+-1]); clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
var params_top = clover2StackIndex-2
var lambda_object = clover2Stack[params_top]
var lambda_params = clover2Stack.slice(params_top+1, params_top+1+1)
var parent_var_num = lambda_object.parentVarNum;
if(!lambda_object.lambda_) { clover2StackIndex -= 1; clover2StackIndex += parent_var_num; }
if(!lambda_object.lambda_) { for(var i=0; i<lambda_params.length; i++) { clover2Stack[clover2StackIndex] = lambda_params[i]; clover2StackIndex++; } }
if(lambda_object.funcName == "") { tmp = lambda_object.function_(); } else { tmp = block_(); }
clover2StackIndex -= 2
if(!lambda_object.lambda_) { clover2StackIndex -= parent_var_num; }
clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
clover2Stack[clover2StackIndex-1] = !clover2Stack[clover2StackIndex-1]
if(clover2Stack[--clover2StackIndex]) { 
clover2Stack[clover2StackIndex] = false; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
clover2GlobalStack[clover2GlobalStackIndex] = clover2Stack[clover2StackIndex-1]; clover2GlobalStackIndex++; clover2StackIndex--;
}
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
clover2GlobalStack[clover2GlobalStackIndex] = clover2Stack[clover2StackIndex-1]; clover2GlobalStackIndex++; clover2StackIndex--;
clover2Stack[clover2StackIndex] = clover2GlobalStack[clover2GlobalStackIndex-1]; clover2StackIndex++; clover2GlobalStackIndex--
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
clover2Stack[clover2StackIndex] = 1; clover2StackIndex++
clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = clover2Stack[clover2StackIndex] + clover2Stack[clover2StackIndex+1]; clover2StackIndex++
clover2Stack[lvar+3] = clover2Stack[clover2StackIndex-1]
clover2Stack[clover2StackIndex] = 1; clover2StackIndex++
clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = clover2Stack[clover2StackIndex] - clover2Stack[clover2StackIndex+1]; clover2StackIndex++
clover2StackIndex -= 1
}
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = true; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
Array.prototype.some__lambda = function (block_)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 4
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].length; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
clover2Stack[lvar+2] = clover2Stack[clover2StackIndex-1]
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = 0; clover2StackIndex++
clover2Stack[lvar+3] = clover2Stack[clover2StackIndex-1]
clover2StackIndex -= 1
while(true) {
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+2]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-2] < clover2Stack[clover2StackIndex-1]; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
if(!clover2Stack[--clover2StackIndex]) { 
break;
}
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-2].items__Number(clover2Stack[clover2StackIndex+-1]); clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
var params_top = clover2StackIndex-2
var lambda_object = clover2Stack[params_top]
var lambda_params = clover2Stack.slice(params_top+1, params_top+1+1)
var parent_var_num = lambda_object.parentVarNum;
if(!lambda_object.lambda_) { clover2StackIndex -= 1; clover2StackIndex += parent_var_num; }
if(!lambda_object.lambda_) { for(var i=0; i<lambda_params.length; i++) { clover2Stack[clover2StackIndex] = lambda_params[i]; clover2StackIndex++; } }
if(lambda_object.funcName == "") { tmp = lambda_object.function_(); } else { tmp = block_(); }
clover2StackIndex -= 2
if(!lambda_object.lambda_) { clover2StackIndex -= parent_var_num; }
clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
if(clover2Stack[--clover2StackIndex]) { 
clover2Stack[clover2StackIndex] = true; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
clover2GlobalStack[clover2GlobalStackIndex] = clover2Stack[clover2StackIndex-1]; clover2GlobalStackIndex++; clover2StackIndex--;
}
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
clover2GlobalStack[clover2GlobalStackIndex] = clover2Stack[clover2StackIndex-1]; clover2GlobalStackIndex++; clover2StackIndex--;
clover2Stack[clover2StackIndex] = clover2GlobalStack[clover2GlobalStackIndex-1]; clover2StackIndex++; clover2GlobalStackIndex--
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
clover2Stack[clover2StackIndex] = 1; clover2StackIndex++
clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = clover2Stack[clover2StackIndex] + clover2Stack[clover2StackIndex+1]; clover2StackIndex++
clover2Stack[lvar+3] = clover2Stack[clover2StackIndex-1]
clover2Stack[clover2StackIndex] = 1; clover2StackIndex++
clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = clover2Stack[clover2StackIndex] - clover2Stack[clover2StackIndex+1]; clover2StackIndex++
clover2StackIndex -= 1
}
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = false; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
Array.prototype.filter__lambda = function (block_)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 4
clover2Stack[clover2StackIndex] = 0; clover2StackIndex++
tmp = new Array(clover2Stack[clover2StackIndex-1]); clover2StackIndex-=1; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
clover2Stack[lvar+2] = clover2Stack[clover2StackIndex-1]
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = 0; clover2StackIndex++
clover2Stack[lvar+3] = clover2Stack[clover2StackIndex-1]
clover2StackIndex -= 1
while(true) {
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].length; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-2] < clover2Stack[clover2StackIndex-1]; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
if(!clover2Stack[--clover2StackIndex]) { 
break;
}
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-2].items__Number(clover2Stack[clover2StackIndex+-1]); clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
var params_top = clover2StackIndex-2
var lambda_object = clover2Stack[params_top]
var lambda_params = clover2Stack.slice(params_top+1, params_top+1+1)
var parent_var_num = lambda_object.parentVarNum;
if(!lambda_object.lambda_) { clover2StackIndex -= 1; clover2StackIndex += parent_var_num; }
if(!lambda_object.lambda_) { for(var i=0; i<lambda_params.length; i++) { clover2Stack[clover2StackIndex] = lambda_params[i]; clover2StackIndex++; } }
if(lambda_object.funcName == "") { tmp = lambda_object.function_(); } else { tmp = block_(); }
clover2StackIndex -= 2
if(!lambda_object.lambda_) { clover2StackIndex -= parent_var_num; }
clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
if(clover2Stack[--clover2StackIndex]) { 
clover2Stack[clover2StackIndex] = clover2Stack[lvar+2]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-2].items__Number(clover2Stack[clover2StackIndex+-1]); clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-2].push(clover2Stack[clover2StackIndex+-1]); clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
clover2GlobalStack[clover2GlobalStackIndex] = clover2Stack[clover2StackIndex-1]; clover2GlobalStackIndex++; clover2StackIndex--;
}
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
clover2GlobalStack[clover2GlobalStackIndex] = clover2Stack[clover2StackIndex-1]; clover2GlobalStackIndex++; clover2StackIndex--;
clover2Stack[clover2StackIndex] = clover2GlobalStack[clover2GlobalStackIndex-1]; clover2StackIndex++; clover2GlobalStackIndex--
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
clover2Stack[clover2StackIndex] = 1; clover2StackIndex++
clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = clover2Stack[clover2StackIndex] + clover2Stack[clover2StackIndex+1]; clover2StackIndex++
clover2Stack[lvar+3] = clover2Stack[clover2StackIndex-1]
clover2Stack[clover2StackIndex] = 1; clover2StackIndex++
clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = clover2Stack[clover2StackIndex] - clover2Stack[clover2StackIndex+1]; clover2StackIndex++
clover2StackIndex -= 1
}
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+2]; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
Array.prototype.find__lambda = function (block_)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 4
clover2Stack[clover2StackIndex] = 0; clover2StackIndex++
tmp = new Array(clover2Stack[clover2StackIndex-1]); clover2StackIndex-=1; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
clover2Stack[lvar+2] = clover2Stack[clover2StackIndex-1]
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = 0; clover2StackIndex++
clover2Stack[lvar+3] = clover2Stack[clover2StackIndex-1]
clover2StackIndex -= 1
while(true) {
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].length; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-2] < clover2Stack[clover2StackIndex-1]; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
if(!clover2Stack[--clover2StackIndex]) { 
break;
}
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-2].items__Number(clover2Stack[clover2StackIndex+-1]); clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
var params_top = clover2StackIndex-2
var lambda_object = clover2Stack[params_top]
var lambda_params = clover2Stack.slice(params_top+1, params_top+1+1)
var parent_var_num = lambda_object.parentVarNum;
if(!lambda_object.lambda_) { clover2StackIndex -= 1; clover2StackIndex += parent_var_num; }
if(!lambda_object.lambda_) { for(var i=0; i<lambda_params.length; i++) { clover2Stack[clover2StackIndex] = lambda_params[i]; clover2StackIndex++; } }
if(lambda_object.funcName == "") { tmp = lambda_object.function_(); } else { tmp = block_(); }
clover2StackIndex -= 2
if(!lambda_object.lambda_) { clover2StackIndex -= parent_var_num; }
clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
if(clover2Stack[--clover2StackIndex]) { 
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-2].items__Number(clover2Stack[clover2StackIndex+-1]); clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
clover2GlobalStack[clover2GlobalStackIndex] = clover2Stack[clover2StackIndex-1]; clover2GlobalStackIndex++; clover2StackIndex--;
}
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
clover2GlobalStack[clover2GlobalStackIndex] = clover2Stack[clover2StackIndex-1]; clover2GlobalStackIndex++; clover2StackIndex--;
clover2Stack[clover2StackIndex] = clover2GlobalStack[clover2GlobalStackIndex-1]; clover2StackIndex++; clover2GlobalStackIndex--
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
clover2Stack[clover2StackIndex] = 1; clover2StackIndex++
clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = clover2Stack[clover2StackIndex] + clover2Stack[clover2StackIndex+1]; clover2StackIndex++
clover2Stack[lvar+3] = clover2Stack[clover2StackIndex-1]
clover2Stack[clover2StackIndex] = 1; clover2StackIndex++
clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = clover2Stack[clover2StackIndex] - clover2Stack[clover2StackIndex+1]; clover2StackIndex++
clover2StackIndex -= 1
}
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
Array.prototype.findIndex__lambda = function (block_)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 4
clover2Stack[clover2StackIndex] = 0; clover2StackIndex++
tmp = new Array(clover2Stack[clover2StackIndex-1]); clover2StackIndex-=1; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
clover2Stack[lvar+2] = clover2Stack[clover2StackIndex-1]
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = 0; clover2StackIndex++
clover2Stack[lvar+3] = clover2Stack[clover2StackIndex-1]
clover2StackIndex -= 1
while(true) {
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].length; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-2] < clover2Stack[clover2StackIndex-1]; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
if(!clover2Stack[--clover2StackIndex]) { 
break;
}
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-2].items__Number(clover2Stack[clover2StackIndex+-1]); clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
var params_top = clover2StackIndex-2
var lambda_object = clover2Stack[params_top]
var lambda_params = clover2Stack.slice(params_top+1, params_top+1+1)
var parent_var_num = lambda_object.parentVarNum;
if(!lambda_object.lambda_) { clover2StackIndex -= 1; clover2StackIndex += parent_var_num; }
if(!lambda_object.lambda_) { for(var i=0; i<lambda_params.length; i++) { clover2Stack[clover2StackIndex] = lambda_params[i]; clover2StackIndex++; } }
if(lambda_object.funcName == "") { tmp = lambda_object.function_(); } else { tmp = block_(); }
clover2StackIndex -= 2
if(!lambda_object.lambda_) { clover2StackIndex -= parent_var_num; }
clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
if(clover2Stack[--clover2StackIndex]) { 
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
clover2GlobalStack[clover2GlobalStackIndex] = clover2Stack[clover2StackIndex-1]; clover2GlobalStackIndex++; clover2StackIndex--;
}
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
clover2GlobalStack[clover2GlobalStackIndex] = clover2Stack[clover2StackIndex-1]; clover2GlobalStackIndex++; clover2StackIndex--;
clover2Stack[clover2StackIndex] = clover2GlobalStack[clover2GlobalStackIndex-1]; clover2StackIndex++; clover2GlobalStackIndex--
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
clover2Stack[clover2StackIndex] = 1; clover2StackIndex++
clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = clover2Stack[clover2StackIndex] + clover2Stack[clover2StackIndex+1]; clover2StackIndex++
clover2Stack[lvar+3] = clover2Stack[clover2StackIndex-1]
clover2Stack[clover2StackIndex] = 1; clover2StackIndex++
clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = clover2Stack[clover2StackIndex] - clover2Stack[clover2StackIndex+1]; clover2StackIndex++
clover2StackIndex -= 1
}
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = -1; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
Array.prototype.forEach__lambda = function (block_)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 3
clover2Stack[clover2StackIndex] = 0; clover2StackIndex++
clover2Stack[lvar+2] = clover2Stack[clover2StackIndex-1]
clover2StackIndex -= 1
while(true) {
clover2Stack[clover2StackIndex] = clover2Stack[lvar+2]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].length; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-2] < clover2Stack[clover2StackIndex-1]; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
if(!clover2Stack[--clover2StackIndex]) { 
break;
}
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+2]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-2].items__Number(clover2Stack[clover2StackIndex+-1]); clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
var params_top = clover2StackIndex-2
var lambda_object = clover2Stack[params_top]
var lambda_params = clover2Stack.slice(params_top+1, params_top+1+1)
var parent_var_num = lambda_object.parentVarNum;
if(!lambda_object.lambda_) { clover2StackIndex -= 1; clover2StackIndex += parent_var_num; }
if(!lambda_object.lambda_) { for(var i=0; i<lambda_params.length; i++) { clover2Stack[clover2StackIndex] = lambda_params[i]; clover2StackIndex++; } }
if(lambda_object.funcName == "") { tmp = lambda_object.function_(); } else { tmp = block_(); }
clover2StackIndex -= 2
if(!lambda_object.lambda_) { clover2StackIndex -= parent_var_num; }
clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+2]; clover2StackIndex++
clover2Stack[clover2StackIndex] = 1; clover2StackIndex++
clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = clover2Stack[clover2StackIndex] + clover2Stack[clover2StackIndex+1]; clover2StackIndex++
clover2Stack[lvar+2] = clover2Stack[clover2StackIndex-1]
clover2Stack[clover2StackIndex] = 1; clover2StackIndex++
clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = clover2Stack[clover2StackIndex] - clover2Stack[clover2StackIndex+1]; clover2StackIndex++
clover2StackIndex -= 1
}
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}
Array.prototype.indexOf__GenericsParametorClass0_Number = function (item,count)
{
        var n = 0;
        for(var i= 0; i<this.length; i++) {
            if(this[i].equals(item)) {
                n++;

                if(n == count) {
                    return i;
                }
            }
        }

        return -1;
    }

    
Array.prototype.join__ = function ()
{
        return this.join();
    }

    
Array.prototype.join__String = function (str)
{
        return this.join(str);
    }

    
Array.prototype.lastIndexOf__GenericsParametorClass0 = function (item)
{
        for(var i= this.length-1; i>=0; i--) {
            if(this[i].equals(item)) {
                return i;
            }
        }

        return -1;
    }
    
Array.prototype.lastIndexOf__GenericsParametorClass0_Number = function (item,fromIndex)
{
        if(fromIndex < 0) {
            fromIndex += this.length;
        }

        if(fromIndex >= this.length) {
            fromIndex = this.length - 1;
        }

        for(var i = fromIndex; i>=0; i--) {
            if(this[i].equals(item)) {
                return i;
            }
        }

        return -1;
    }

    
Array.prototype.map__lambda = function (trans)
{
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-2
clover2StackIndex = lvar + 4
clover2Stack[clover2StackIndex] = 0; clover2StackIndex++
tmp = new Array(clover2Stack[clover2StackIndex-1]); clover2StackIndex-=1; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
clover2Stack[lvar+2] = clover2Stack[clover2StackIndex-1]
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = 0; clover2StackIndex++
clover2Stack[lvar+3] = clover2Stack[clover2StackIndex-1]
clover2StackIndex -= 1
while(true) {
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-1].length; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
tmp = clover2Stack[clover2StackIndex-2] < clover2Stack[clover2StackIndex-1]; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
if(!clover2Stack[--clover2StackIndex]) { 
break;
}
clover2Stack[clover2StackIndex] = clover2Stack[lvar+2]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+1]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-2].items__Number(clover2Stack[clover2StackIndex+-1]); clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
var params_top = clover2StackIndex-2
var lambda_object = clover2Stack[params_top]
var lambda_params = clover2Stack.slice(params_top+1, params_top+1+1)
var parent_var_num = lambda_object.parentVarNum;
if(!lambda_object.lambda_) { clover2StackIndex -= 1; clover2StackIndex += parent_var_num; }
if(!lambda_object.lambda_) { for(var i=0; i<lambda_params.length; i++) { clover2Stack[clover2StackIndex] = lambda_params[i]; clover2StackIndex++; } }
if(lambda_object.funcName == "") { tmp = lambda_object.function_(); } else { tmp = trans(); }
clover2StackIndex -= 2
if(!lambda_object.lambda_) { clover2StackIndex -= parent_var_num; }
clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
tmp = clover2Stack[clover2StackIndex-2].push(clover2Stack[clover2StackIndex+-1]); clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+3]; clover2StackIndex++
clover2Stack[clover2StackIndex] = 1; clover2StackIndex++
clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = clover2Stack[clover2StackIndex] + clover2Stack[clover2StackIndex+1]; clover2StackIndex++
clover2Stack[lvar+3] = clover2Stack[clover2StackIndex-1]
clover2Stack[clover2StackIndex] = 1; clover2StackIndex++
clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = clover2Stack[clover2StackIndex] - clover2Stack[clover2StackIndex+1]; clover2StackIndex++
clover2StackIndex -= 1
}
clover2Stack[clover2StackIndex] = null; clover2StackIndex++;
clover2StackIndex -= 1
clover2Stack[clover2StackIndex] = clover2Stack[lvar+2]; clover2StackIndex++
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2
return tmp
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+2;
return tmp;
}

}
var clover2Stack = new Array(256); var clover2StackIndex = 0;
var funcToLambda = new Map();
var exception = new Object()
function typeOf(obj) { return Object.prototype.toString.call(obj).slice(8, -1).toLowerCase(); }
function typeOfNativeObject(obj) { var object_type = typeOf(obj); return object_type == 'array' || object_type == 'number' || object_type == 'string' || object_type == 'map'; }
function typeOfNativeObject(obj) { var object_type = typeOf(obj); return object_type == 'array' || object_type == 'number' || object_type == 'string' || object_type == 'map'; }
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-0
clover2StackIndex = lvar + 0
clover2Stack[clover2StackIndex] = "AAA"; clover2StackIndex++
clover2Stack[clover2StackIndex] = "BBB"; clover2StackIndex++
clover2Stack[clover2StackIndex] = "CCC"; clover2StackIndex++
tmp = [clover2Stack[clover2StackIndex+-3],clover2Stack[clover2StackIndex+-2],clover2Stack[clover2StackIndex+-1]]
clover2StackIndex -= 3;
clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;
var lambda__ = function lambda1 () {
var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;
var tmp;
var clover2StackBefore = null; var clover2StackIndexBefore = -1;
var lvar = clover2StackIndex-1
clover2StackIndex = lvar + 1
var _lambda = funcToLambda.get('lambda1');
if(_lambda != undefined && _lambda.listener) { clover2StackBefore = clover2Stack; clover2StackIndexBefore = clover2StackIndex; clover2Stack = clover2Stack.slice(0); lvar = 0; clover2StackIndex = lvar + 1 }
if(_lambda != undefined && !_lambda.lambda_) { _lambda.copyParentStack(lvar); }
if(_lambda != undefined && !_lambda.lambda_) { for(var i=0; i<lambda1.arguments.length; i++) { clover2Stack[lvar+_lambda.parentVarNum+i] = lambda1.arguments[i]; } }
clover2Stack[clover2StackIndex] = clover2Stack[lvar+0]; clover2StackIndex++
tmp = System.println__String(clover2Stack[clover2StackIndex+-1]); clover2StackIndex -= 1; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
var lambda = funcToLambda.get('lambda1');
if(lambda != undefined && !_lambda.lambda_) { lambda.copyBackParentStack(lvar); }
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+1;
return tmp;
return clover2Stack[clover2StackIndex-1];
}
clover2Stack[clover2StackIndex] = new Lambda().constructor__Function_bool_Number_String_Number_Number(lambda__, false, 0, "", 1, lvar); clover2StackIndex++;
funcToLambda.set('lambda1', clover2Stack[clover2StackIndex-1])
tmp = clover2Stack[clover2StackIndex-2].forEach__lambda(clover2Stack[clover2StackIndex+-1]); clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++
clover2StackIndex -= 1
if(clover2StackBefore != null) { clover2Stack = clover2StackBefore; clover2StackIndex = clover2StackIndexBefore; }
tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex=lvar+0;
