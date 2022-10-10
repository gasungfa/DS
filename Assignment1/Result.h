#ifndef RESULT_H
#define RESULT_H

enum Result{

    Success = 0,

    CommandFileNotExist = 100,
    LoadFileNotExist = 100,

    AddError = 200,
    InvalidVertexKey,
    GraphNotExist,
    InvalidAlgorithm,
    NegativeCycleDetected,

    ModifyError = 300,
    MoveError = 400,
    Print_Error = 500,
    Search_Error = 600,
    Select_Error = 700,
    WrongInstruction = 777,
    EditError = 800,
    CloseNum = 1000,
};

#endif