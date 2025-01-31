#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
	SM.setup();
	IM.setup();

	//ofSetWindowPosition(2000, 0);
	ofSetFullscreen(true);
	//ofHideCursor();


	//-------------------------------------------
	// fake interactive
	prevMouse.set(mouseX, mouseY);
	//-------------------------------------------
	IM.setLEDs(1,1,1,1);

}

//--------------------------------------------------------------
void ofApp::update(){
	SM.update();
	IM.update();



	//-------------------------------------------
	// fake interactive
//	ofPoint currentPoint(mouseX, mouseY);
//	ofPoint diff = currentPoint - prevMouse;
//	diff /= ofPoint(ofGetWidth(), ofGetHeight());
//	if (bToggleUseRecording == false) {
//
//			SM.scenes[SM.currentScene]->updateInteractiveParams(diff.x, 0);
//			SM.scenes[SM.currentScene]->updateInteractiveParams(diff.y, 1);
//	}
//	prevMouse.set(mouseX, mouseY);
//    
//    
    
    // interactivity...
   
    
	//-------------------------------------------


}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(10);
	ofPushMatrix();


	// cout << "------------------ " << SM.pctDelay << endl;

#ifdef DRAW_TWO_UP

//  ofLine(0,0,520,520);
//  ofLine(520,0, 520+520,520);

    
#ifndef BIG_TV
    
    ofPushMatrix();
    ofTranslate(0,(1080-960));
    ofScale(960.0/720.0, 960.0/720.0);
	SM.draw();
    ofPopMatrix();
    
#endif
    

    if (SM.pctDelay < SCENE_PRE_TRANSITION_FADE || SM.isTransitioning) {
        IM.turnOffLEDs();
    }
	if (SM.pctDelay < FADE_DELAY_MIN) {
		// typing is happening...
		//SM.codeFbo.draw(0, 0, 520,520);
	}
    if (SM.shouldDrawScene && !SM.isTransitioning) {
		int numParams = MIN(SM.scenes[SM.currentScene]->midiKnobs.size(),4);
//        cout << "Number of parameters: " << numParams << endl;
		IM.setCurrentSceneParameterCount(numParams);
	}
    
    
#ifndef BIG_TV
	
    
    ofPushMatrix();
    ofTranslate(960,(1080-960));
    ofScale(960.0/720.0, 960.0/720.0);
    SM.codeFbo.draw(0,0);
//    ofLine(0,0,720, 720);
//    ofLine(0,720,0, 720);
    
    ofPopMatrix();
    
    //ofPushMatrix();
	
    //ofTranslate(720,0);
	//SM.codeFbo.draw(0, 0, 720,720);
	//ofPopMatrix();
     SM.drawGui();
#endif
    
#ifdef BIG_TV

    ofPushMatrix();
        float h = 504 * 1920.0/(float)(504+504);
        ofTranslate(0,(1080-h)*0.5);
        ofScale(1920.0/(float)(504+504), 1920.0/(float)(504+504));
        SM.draw();
    
    
    ofPopMatrix();

    ofPushMatrix();

    ofTranslate(h, (1080-h)*0.5);
    SM.codeFbo.draw(0, 0, 504*2, 504*2);
        //SM.drawType();
    ofPopMatrix();
    
     SM.drawGui();
#endif
    


#elif defined DRAW_ONE_BIG
	float scale = 1080.0/(float)(504);
	float w = scale * 504;
	ofTranslate((1920-w)*0.5, 0);
	ofScale(scale, scale);
	SM.draw();
       SM.drawGui();
#else
	SM.draw();
       SM.drawGui();
#endif


	ofPopMatrix();
    
    
    if (SM.bDrawGui){
		stringstream ss;
		ss << "interaction mode " << (IM.bInteracting == true ? "interacting" : "playback") << endl;
        for (int i = 0; i < 4; i++){
            ss <<  "knob value " << i << " = " << IM.prevPacket.knobValues[i] * 100 << endl << endl;
        }
		ss << endl;
		ss << "bUpdateParamFromRecording: " << (string)(SM.scenes[SM.currentScene]->bUpdateParamFromRecording?"TRUE":"FALSE") << endl;
		ss << "bToggleUseRecording: " << (string)(bToggleUseRecording?"TRUE":"FALSE") << endl;
		
		ss << "scene has rec data:  " << (string)(SM.scenes[SM.currentScene]->hasRecData()?"TRUE":"FALSE") << endl;
		ss << "scene rec data size: " << SM.scenes[SM.currentScene]->recData.size() << endl;
		ss << "Elapsed time: " << SM.scenes[SM.currentScene]->getElapsedTimef() << endl;
		
		
		ofDrawBitmapStringHighlight(ss.str(), 100, 540);
		SM.sync.drawDebug();
    }

}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key == OF_KEY_RIGHT) {
		SM.advanceScene();
	} else if (key == OF_KEY_LEFT) {
		SM.regressScene();
	}

	if (key == 'f') {
		ofToggleFullscreen();
	}

	if (key == 's') {
		SM.screenGrab();
	}

	if (key == 'h') {
		ofHideCursor();
        SM.bDrawGui = false;
        
	}
	if (key == 'H') {
		ofShowCursor();
        SM.bDrawGui = true;
    }



	if (key == 'i') {
		bToggleUseRecording = !bToggleUseRecording;
		for (int i = 0; i < SM.scenes.size(); i++) {
			SM.scenes[i]->bUpdateParamFromRecording = bToggleUseRecording;
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){


}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
