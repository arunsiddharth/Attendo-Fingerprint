//enroll to cloud given sid,id,class_name,teacher_name
int enroll_cloud(){
    Sense_Values = "tid=";
    Sense_Values += teacher_name;
    Sense_Values += "&cname=";
    Sense_Values += class_name;
    Sense_Values += "&sid=";
    Sense_Values +=sid;
    Sense_Values += "&id=";
    Sense_Values += String(id);
    if(get_enroll()){Sense_Values.remove(0,Sense_Values.length());return 1;}
    else{Sense_Values.remove(0,Sense_Values.length()); return 0;}
}

