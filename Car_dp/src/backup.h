

bool wordExistance(String phrase, String word){

  int wordIndex = phrase.indexOf(word);

  if (wordIndex >= 0){

    return true;

  }else{

    return false;
    
  }


}


String beforeORafter(String sourceStr, String Target, int dataIndex, bool debug = false){

  int targetLength = Target.length();

  int index = sourceStr.indexOf(Target);

  String out = "";  
  
  if(dataIndex < 1){

    // before            //start // end
    out = sourceStr.substring(0, index);

  }else{

    // after
    out = sourceStr.substring(index + targetLength);
    
  }

  if(debug){

    Serial.print("beforeORafter OUT: ");
    Serial.println(out);
    
  }

  return out;

}




bool findDataInList(String dataTofind, String *listData, int listSize){

  bool foundData = false;

  for(int numData = 0; numData < listSize; numData++){

    String targetSTR = listData[numData];

    if(dataTofind == targetSTR){

      foundData = true;
      break;
              
    } 
      
  } 

  return foundData;

}


String delIndex(String word, int index, char mode){
	
	// from index 0 to 10
	
	String outChar;
	
	String out = "";
	
	for (int num = 0; num < word.length(); num++) {
		
		
		char currentChar = word[num];
		
		if(index != num){
			
			out += currentChar;
			
		}else{
			
			outChar = currentChar;
      
		}
		
	}
	
	if(mode == 'd'){
		
		return out;
			
	}else{
		
		return outChar;
	
	}

}


String del(String word, String target) {

  String wordCollector = "";
  
  String out = "";
  
  int skipsCounter = 0;
  bool startSkipping= false;
  
  int len = word.length();

  for (int numAlpha = 0; numAlpha < len; numAlpha++) {
  	
    char currentChar = word[numAlpha];
    
    int targetLen = target.length();
    
    int collectedWordLen = wordCollector.length();
    
    if(targetLen == collectedWordLen){
    	
      if(target != wordCollector){
        
        // delete fisrt char
        
        String firstChar = delIndex(wordCollector, 0, 'r');
        
        out += firstChar;
        
        wordCollector = delIndex(wordCollector, 0, 'd');

        wordCollector += currentChar;
        
      }else if (target == wordCollector){
        
        wordCollector = currentChar;
        
      }	
    	
    }else{
      
      wordCollector += currentChar;
        
    }
	
    if(numAlpha == len - 1 && target != wordCollector) {
      
      out += wordCollector;
      
    }
 
  }

  return out;
  
}


String sliceStreamIntoOrder(String word, String *listData, int listSize, bool removeSpaces = true, bool debug = false) {

  // the first index will be reserved for table size
  
  // Serial.print("listSize: ");
  // Serial.println(listSize);

  // full up the list  

  String wordCollector = "";

  String outString = "";

  if(removeSpaces){

    word = del(word, " ");

    word = del(word, "\n");
    
  }

 

  int len = word.length();  

  int wordsCounter = 0; 

  // Serial.print("lenListData: ");
  // Serial.println(lenListData);
    
  for (int numChar = 0; numChar < len; numChar++) {

    char currentChar = word[numChar];

    // Serial.print("currentChar: ");
    // Serial.println(currentChar); 

    bool foundData = findDataInList(wordCollector, listData, listSize);
       
    if (foundData) {

      outString += wordCollector + String(wordsCounter);

      wordsCounter += 1;
      
      wordCollector = "";

    }else if(numChar == len - 1){
      
      outString += wordCollector + String(wordsCounter);
      
      wordCollector = "";

      wordsCounter += 1;
    
    }else{

      wordCollector += currentChar;
      
    }
    
  }

  
  if(debug){

    Serial.print("outString: ");
    Serial.println(outString);    

  }
 
  String hostString = outString; 

  if(debug){

    Serial.print("hostString: ");
    Serial.println(hostString); 
    
  }
  
  // adding length in the beginning
  outString =  String(wordsCounter) + "lenCMDS-";

  outString += hostString;
  
  if(debug){
    
    Serial.print("outString: ");
    Serial.println(outString); 

  }

  return outString;      

}




