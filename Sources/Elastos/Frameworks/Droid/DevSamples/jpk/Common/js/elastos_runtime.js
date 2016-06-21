module.exports = function (api) {

var sEcoName = "/data/temp/node/bin/Elastos.DevSamples.Node.CarRuntime.eco";
var sClassName = "Elastos.DevSamples.Node.CarRuntime.CCarRuntime";
var _Runtime_Native = api.require(sEcoName, sClassName);

var _getModuleInfo = function (asEcoName) {
    return _Runtime_Native.Test_Require_ModuleInfo(asEcoName);
};

var CarDataType = {
    Int16       : 1,
    Int32       : 2,
    Int64       : 3,
    Byte        : 4,
    Float       : 5,
    Double      : 6,
    Char32      : 7,
    String      : 8,
    Boolean     : 9,
    EMuid       : 10,
    EGuid       : 11,
    ECode       : 12,
    LocalPtr    : 13,
    LocalType   : 14,
    Enum        : 15,
    CarArray    : 16,
    CppVector   : 17,
    Struct      : 18,
    Interface   : 19
};

var CarToJsDataTypeMap = {
    boolean:[
        CarDataType.Boolean,
    ],
    number:[
        CarDataType.Int16,
        CarDataType.Int32,
        CarDataType.Int64,
        CarDataType.Byte,
        CarDataType.Float,
        CarDataType.Double,
        CarDataType.ECode,
        CarDataType.Enum,
    ],
    string:[
        //CarDataType.Char8,
        //CarDataType.Char16,
        CarDataType.Char32,
        //CarDataType.CString,
        CarDataType.String,
        //CarDataType.StringBuf,
    ],
    array:[
        CarDataType.CarArray,
        //CarDataType.BufferOf,
        //CarDataType.MemoryBuf,
        CarDataType.CppVector,
    ],
    object:[
        CarDataType.EMuid,
        CarDataType.EGuid,
        CarDataType.LocalPtr,
        CarDataType.LocalType,
        CarDataType.Struct,
        CarDataType.Interface,
    ],
    //other:[
    //    CarDataType.LocalPtr,
    //    CarDataType.LocalType,
    //],
};

var ParamIOAttribute = {
        In : 0,
        CalleeAllocOut : 1,
        CallerAllocOut : 2,
}

function getDataTypeCarString(ai_datatype){
    var sRet = 'Not Defined DataType';

    for(var p in CarDataType) {
        if (CarDataType[p] == ai_datatype) {
            sRet = p;
            break;
        }
    }

    return sRet;
}

function getDataTypeJavascriptString(ai_datatype){
    var sRet = 'Not Defined DataType';

    var bFound = false;
    for(var p in CarToJsDataTypeMap) {
        var a = CarToJsDataTypeMap[p];
        for(var i = 0,im = a.length; i<im; i++) {
            if (a[i] == ai_datatype) {
                sRet = p;
                bFound = true;
                break;
            }
        }
        if (bFound) {
            break;
        }
    }

    return sRet;
}

function classinfo__createObject(oModuleInfo,oClassInfo){
    var newObject;

    var bCreateOnUIThread = false;

    if(typeof(oModuleInfo)=='string') {
        //oModuleInfo = Elastos.Runtime.getModuleInfo(oModuleInfo);
        oModuleInfo = _getModuleInfo(oModuleInfo);
    }

    var sClassName = "null";
    if(typeof(oClassInfo)=='string') {
        sClassName = oClassInfo;
        elog('====classinfo__createObject====begin==0.0==ClassName:'+sClassName);
        oClassInfo = oModuleInfo.GetClassInfo(oClassInfo);
        elog('====classinfo__createObject====begin==0.1==ClassName:'+sClassName);
        sClassName = oClassInfo.GetName();
        elog('====classinfo__createObject====begin==0.2==ClassName:'+sClassName);
    }
    else {
        sClassName = oClassInfo.GetName();
        elog('====classinfo__createObject====begin==0.3==ClassName:'+sClassName);
    }

    if (sClassName == "Elastos.Droid.Widget.CPopupWindow") {
        bCreateOnUIThread = true;
    }

    var length = arguments.length;
    if(length==2){
        //newObject = oClassInfo.CreateObject();
        if (bCreateOnUIThread) {
            elog('====classinfo__createObject========oClassInfo.RemoteCreateObject');
            newObject = oClassInfo.RemoteCreateObject();
        }
        else {
            elog('====classinfo__createObject========oClassInfo.LocalCreateObject');
            newObject = oClassInfo.LocalCreateObject();
        }
    }
    else {
        var aConstructorInfos = oClassInfo.GetAllConstructorInfos();
        var oConstructorInfo;
        //var paramCount = length - 2;
        var paramCount = length - 1;
        for(var i=0, im=aConstructorInfos.length; i<im; i++){
            oConstructorInfo = aConstructorInfos[i];

            var _paramCount = oConstructorInfo.GetParamCount();
            //var _paramInfos = oConstructorInfo.GetAllParamInfos();
            //var _paramCount = _paramInfos.length;

            elog('====classinfo__createObject===='+i+' _paramCount:'+_paramCount+'===paramCount:'+paramCount+'===========');

            //if (_paramCount == paramCount) {
            if (_paramCount == paramCount) {
                var bSameArgs = true;
                var aParamInfos = oConstructorInfo.GetAllParamInfos();
                //for(var j = 0, jm = paramCount; j<jm; j++) {
                for(var j = 0, jm = paramCount -1; j<jm; j++) {
                    var paramInfo = aParamInfos[j];
                    var oTypeInfo = paramInfo.GetTypeInfo();

                    var iDataType = oTypeInfo.GetDataType();
                    var sJsDataType = getDataTypeJavascriptString(iDataType);

                    var arg_in = arguments[j+2];
                    var type_in = typeof(arg_in);

                    elog("====classinfo__createObject====param:"+j+" js type:"+sJsDataType+" carType:"+type_in+" carDataType:"+iDataType);

                    if (sJsDataType == type_in) {
                        if (iDataType == CarDataType.Interface) {
                            //TODO:compare the interface name
                            continue;
                        }
                        else if (iDataType == CarDataType.LocalPtr) {
                            //TODO:compare the localptr element type
                            //continue;

                            var oElementTypeInfo = oTypeInfo.GetTargetTypeInfo();
                            var iElementDataType = oElementTypeInfo.GetDataType();

                            //elog('==============classinfo__createObject ======find method====LocalPtr====element type:'+iElementDataType+'====' + ([1,2] instanceof Array) );
                            elog('==============classinfo__createObject ======find method====LocalPtr====element type:'+iElementDataType);

                            switch (iElementDataType) {
                                case CarDataType.Interface:
                                    break;
                                case CarDataType.CarArray:
                                    if (typeof arg_in.GetClassId == 'function') bSameArgs = false;
                                    //elog("=========insatanceof=====1==========="+bSameArgs);
                                    //bSameArgs = (arg_in instanceOf Array);
                                    //elog("=========insatanceof=====2==========="+bSameArgs);
                                    break;
                                default:
                                    //TODO
                                    break;
                            }

                            if (bSameArgs) continue;
                            //continue;
                        }
                        else {
                            continue;
                        }
                    }

                    bSameArgs = false
                    break;
                }
                if (bSameArgs) break;
            }
        }

        var bFoundConstructor = (i < im);
        if (!bFoundConstructor) {
            elog("====classinfo__createObject====can not find constructor : " + sClassName);
            return null;
        }
        else {
            elog("====classinfo__createObject====find constructor : " + sClassName);
        }

        var aParamInfos = oConstructorInfo.GetAllParamInfos();
        var oArgumentList = oConstructorInfo.CreateArgumentList();

        //for(var i = 0, im = paramCount; i<im; i++) {
        for(var i = 0, im = paramCount - 1; i<im; i++) {
            var paramInfo = aParamInfos[i];
            var oTypeInfo = paramInfo.GetTypeInfo();

            var iDataType = oTypeInfo.GetDataType();
            var sJsDataType = getDataTypeJavascriptString(iDataType);

            var arg = arguments[i+2];
            switch (iDataType) {
                case CarDataType.Int16:
                    oArgumentList.SetInputArgumentOfInt16(i,arg);
                    break;
                case CarDataType.Int32:
                    oArgumentList.SetInputArgumentOfInt32(i,arg);
                    break;
                case CarDataType.Int64:
                    oArgumentList.SetInputArgumentOfInt64(i,arg);
                    break;
                case CarDataType.Byte:
                    oArgumentList.SetInputArgumentOfByte(i,arg);
                    break;
                case CarDataType.Float:
                    oArgumentList.SetInputArgumentOfFloat(i,arg);
                    break;
                case CarDataType.Double:
                    oArgumentList.SetInputArgumentOfDouble(i,arg);
                    break;
                //case CarDataType.Char8:
                //case CarDataType.Char16:
                case CarDataType.Char32:
                    //oArgumentList.SetInputArgumentOfChar(i,arg);
                    oArgumentList.SetInputArgumentOfString(0,String(arg));
                    break;
                case CarDataType.String:
                    oArgumentList.SetInputArgumentOfString(i,arg);
                    break;
                case CarDataType.Boolean:
                    oArgumentList.SetInputArgumentOfBoolean(i,arg);
                    break;
                //case CarDataType.EMuid:
                //case CarDataType.EGuid:
                case CarDataType.ECode:
                    oArgumentList.SetInputArgumentOfECode(i,arg);
                    break;
                //case CarDataType.LocalPtr:
                //case CarDataType.LocalType:
                case CarDataType.Enum:
                    oArgumentList.SetInputArgumentOfEnum(i,arg);
                    break;
                //case CarDataType.CarArray:
                //case CarDataType.StructPtr:
                case CarDataType.Interface:
                    //oArgumentList.SetInputArgumentOfObjectPtr(i,arguments[i+2]);
                    oArgumentList.SetInputArgumentOfObjectPtr(i,arg);
                    break;
                case CarDataType.LocalPtr:
                    //to be finished
                    elog('==============classinfo__createObject ===========LocalPtr====begin====');

                    var oElementTypeInfo = oTypeInfo.GetTargetTypeInfo();
                    var iElementDataType = oElementTypeInfo.GetDataType();
                    elog('==============classinfo__createObject ===========LocalPtr====element type:'+iElementDataType);

                    switch (iElementDataType) {
                        case CarDataType.CarArray:
                            //oArgumentList.SetInputArgumentOfObjectPtr(i,arg);

                            //oArgumentList.SetInputArgumentOfLocalPtr(i,arguments[i+2]);
                            var tmp = [1,2,3];
                            oArgumentList.SetInputArgumentOfLocalPtr(tmp,i,arguments[i+2]);
                            break;
                        default:
                            //oArgumentList.SetInputArgumentOfObjectPtr(i,arg);

                            //oArgumentList.SetInputArgumentOfLocalPtr(i,arguments[i+2]);
                            var tmp = [1,2,3];
                            oArgumentList.SetInputArgumentOfLocalPtr(tmp,i,arguments[i+2]);
                            break;
                    }
                    elog('==============classinfo__createObject ===========LocalPtr====end====');
                    break;
                default:
                    var sCarDataType = getDataTypeCarString(iDataType);
                    elog('==============classinfo__createObject ===========argument type: to be finished===========rc:'+ i +'======datatype:'+iDataType);
                    break;
            }
        }

        //var paramInfo = aParamInfos[i];
        //oArgumentList.SetOutputArgumentOfObjectPtr(i,arg);

        //var aa=[];
        //for (var p in oConstructorInfo)aa.push(p);
        //var sAnnotation = oConstructorInfo.GetAnnotation();

        //newObject = oConstructorInfo.CreateObject(oArgumentList);
        if (bCreateOnUIThread) {
            elog('====classinfo__createObject====begin====1.1====RemoteCreateObject');
            newObject = oConstructorInfo.RemoteCreateObject(oArgumentList);
        }
        else {
            elog('====classinfo__createObject====begin====1.1====LocalCreateObject');
            newObject = oConstructorInfo.LocalCreateObject(oArgumentList);
        }

        elog('====classinfo__createObject====begin====2====');
    }

    elog('====classinfo__createObject====begin====3====');

    return newObject;
}   //classinfo__createObject

return {
    getModuleInfo : _getModuleInfo,
    createObject : classinfo__createObject,
};

};  //exports