#include <iostream>
#include <fprint.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

const char * finger_path = "/tmp/finger.pgm";
const char * finger_path_enroll_1 = "/tmp/finger_enroll_1.pgm";
const char * finger_path_enroll_2 = "/tmp/finger_enroll_2.pgm";
const char * finger_path_identify = "/tmp/finger_identify.pgm";
const char * finger_path_verify = "/tmp/finger_verify.pgm";

// Avoid segmentation fault error
struct fp_print_data * gallery_1 [1];
struct fp_print_data * gallery_2 [2];
struct fp_print_data * gallery_3 [3];
struct fp_print_data * gallery_4 [4];
struct fp_print_data * gallery_5 [5];
struct fp_print_data * gallery_6 [6];
struct fp_print_data * gallery_7 [7];
struct fp_print_data * gallery_8 [8];
struct fp_print_data * gallery_9 [9];
struct fp_print_data * gallery_10 [10];
struct fp_print_data * gallery_11 [11];
struct fp_print_data * gallery_12 [12];
struct fp_print_data * gallery_13 [13];
struct fp_print_data * gallery_14 [14];
struct fp_print_data * gallery_15 [15];
struct fp_print_data * gallery_16 [16];
struct fp_print_data * gallery_17 [17];
struct fp_print_data * gallery_18 [18];
struct fp_print_data * gallery_19 [19];
struct fp_print_data * gallery_20 [20];
struct fp_print_data * gallery_21 [21];
struct fp_print_data * gallery_22 [22];
struct fp_print_data * gallery_23 [23];
struct fp_print_data * gallery_24 [24];
struct fp_print_data * gallery_25 [25];
struct fp_print_data * gallery_26 [26];
struct fp_print_data * gallery_27 [27];
struct fp_print_data * gallery_28 [28];
struct fp_print_data * gallery_29 [29];
struct fp_print_data * gallery_30 [30];
struct fp_print_data * gallery_31 [31];
struct fp_print_data * gallery_32 [32];
struct fp_print_data * gallery_33 [33];
struct fp_print_data * gallery_34 [34];
struct fp_print_data * gallery_35 [35];
struct fp_print_data * gallery_36 [36];
struct fp_print_data * gallery_37 [37];
struct fp_print_data * gallery_38 [38];
struct fp_print_data * gallery_39 [39];
struct fp_print_data * gallery_40 [40];
struct fp_print_data * gallery_41 [41];
struct fp_print_data * gallery_42 [42];
struct fp_print_data * gallery_43 [43];
struct fp_print_data * gallery_44 [44];
struct fp_print_data * gallery_45 [45];
struct fp_print_data * gallery_46 [46];
struct fp_print_data * gallery_47 [47];
struct fp_print_data * gallery_48 [48];
struct fp_print_data * gallery_49 [49];
struct fp_print_data * gallery_50 [50];


string path_fprint = "/free/CI24/fprint/prints/0002/00000000/";

// Logic to avoid segmentation fault error
struct fp_print_data ** get_gallery_obj(int size) {
	switch(size) {
		case 1:
			return gallery_1;
		case 2:
			return gallery_2;
		case 3: 
			return gallery_3;
		case 4:
			return gallery_4;
		case 5: 
			return gallery_5;
		case 6: 
			return gallery_6;
		case 7: 
			return gallery_7;
		case 8: 
			return gallery_8;
		case 9: 
			return gallery_9;
		case 10: 
			return gallery_10;
		case 11:
			return gallery_11;
		case 12:
			return gallery_12;
		case 13: 
			return gallery_13;
		case 14:
			return gallery_14;
		case 15: 
			return gallery_15;
		case 16: 
			return gallery_16;
		case 17: 
			return gallery_17;
		case 18: 
			return gallery_18;
		case 19: 
			return gallery_19;
		case 20: 
			return gallery_20;
		case 21:
			return gallery_21;
		case 22:
			return gallery_22;
		case 23: 
			return gallery_23;
		case 24:
			return gallery_24;
		case 25: 
			return gallery_25;
		case 26: 
			return gallery_26;
		case 27: 
			return gallery_27;
		case 28: 
			return gallery_28;
		case 29: 
			return gallery_29;
		case 30: 
			return gallery_30;
		case 31:
			return gallery_31;
		case 32:
			return gallery_32;
		case 33: 
			return gallery_33;
		case 34:
			return gallery_34;
		case 35: 
			return gallery_35;
		case 36: 
			return gallery_36;
		case 37: 
			return gallery_37;
		case 38: 
			return gallery_38;
		case 39: 
			return gallery_39;
		case 40: 
			return gallery_40;
		case 41:
			return gallery_41;
		case 42:
			return gallery_42;
		case 43: 
			return gallery_43;
		case 44:
			return gallery_44;
		case 45: 
			return gallery_45;
		case 46: 
			return gallery_46;
		case 47: 
			return gallery_47;
		case 48: 
			return gallery_48;
		case 49: 
			return gallery_49;
		case 50: 
		default:
			return gallery_50;
	}
}

bool exists_file (const std::string& name) {
	return ( access( name.c_str(), F_OK ) != -1 ); 
}

struct fp_dscv_dev *discover_device(struct fp_dscv_dev **discovered_devs)
{
	struct fp_dscv_dev *ddev = discovered_devs[0];
	struct fp_driver *drv;
	if (!ddev)
		return NULL;
	
	drv = fp_dscv_dev_get_driver(ddev);
	cout << "Found device claimed by" << fp_driver_get_full_name(drv) << " driver" << endl;
	return ddev;
}

struct fp_print_data ** create_object(int size) {
	
}

struct fp_dev *initialize_fp() {
	int r = 1;
	r = fp_init();

	if (r < 0) {
		cout << "Error: Fprint Initialized" << endl;
		fp_exit();
		return NULL;
	}
	
	struct fp_dscv_dev **discovered_devs;	
	discovered_devs = fp_discover_devs();
	if (!discovered_devs) {
		cout <<  "Error: Discover Devices" << endl;
		fp_exit();
		return NULL;
	}

	struct fp_dscv_dev *ddev;
	ddev = discover_device(discovered_devs);
	if (!ddev) {
		fp_dscv_devs_free(discovered_devs);
		cout << "Error: Discover Device" << endl;
		fp_exit();
		return NULL;
	}

	struct fp_dev *dev;
	dev = fp_dev_open(ddev);
	fp_dscv_devs_free(discovered_devs);
	if (!dev) {
		cout << "Error: Device Open" << endl;
		fp_exit();
		return NULL;
	}

	if (!fp_dev_supports_imaging(dev)) {
		cout << "Error: Imaging capabilities" << endl;
		fp_dev_close(dev);
		fp_exit();
		return NULL;	
	}

	fpi_dev_set_nr_enroll_stages(dev, 2);
	return dev;
}


int run_capture() {
	if (exists_file(finger_path) == true) {
		string cmd = "rm \"" + string(finger_path) + "\"";
		cout << "Message: Executing " << cmd << endl;
		system(cmd.c_str()); 
	}
	
	struct fp_dev* dev = initialize_fp();
	
	if (dev == NULL) {
		return 1;
	}
	
	struct fp_img *img = NULL;
	cout << "Message: Put Finger" << endl;
	
	int r = fp_dev_img_capture(dev, 0, &img);
	if (r) {
		cout << "Error: Image Capture code: " << r << endl;
		fp_dev_close(dev);
		fp_exit();
		return 1;	
	}
	
	fp_img_standardize(img);
	
	char c_path[100];
	strcpy(c_path, finger_path);
	
	r = fp_img_save_to_file(img, c_path);
	fp_img_free(img);
	
	if (r) {
		cout << "Error: Image Save" << r << endl;
		fp_dev_close(dev);
		fp_exit();
		return 1;
	} 
		
	cout << "Success: Done!" << endl;
	fp_dev_close(dev);
	fp_exit();
	return 0;	
}

int run_enroll(int person) {
	if (person < 0 || person >= 50) {
		cout << "Error: Invalid person: " << person << endl;
		return 1;
	}
	
	if (exists_file(finger_path_enroll_1) == true) {
		string cmd = "rm \"" + string(finger_path_enroll_1) + "\"";
		cout << "Message: Executing " << cmd << endl;
		system(cmd.c_str()); 
	}
	
	if (exists_file(finger_path_enroll_2) == true) {
		string cmd = "rm \"" + string(finger_path_enroll_2) + "\"";
		cout << "Message: Executing " << cmd << endl;
		system(cmd.c_str()); 
	}
	
	int r = 1; 

	struct fp_dev* dev = initialize_fp();
	if (dev == NULL) {
		return 1;
	}

	struct fp_img *img = NULL;

	struct fp_print_data *enrolled_print;
	
	int index = 0;
	while(true) {
		usleep(500 * 1000);
		cout << "Message: Put Finger" << endl;


		// Enroll routine
		r = fp_enroll_finger_img(dev, &enrolled_print, &img);
		if (r < 0) {
			cout << "Error: Enrolling Code " << r << endl;	
			break;
		}
		
		if (img) {
			int r_image;
			if (index == 0) {
				char c_path[100];
				strcpy(c_path, finger_path_enroll_1);
				r_image = fp_img_save_to_file(img, c_path);
			}
			else {
				char c_path[100];
				strcpy(c_path, finger_path_enroll_2);
				r_image = fp_img_save_to_file(img, c_path);
			}
			
			fp_img_free(img);
			index++;
			
			if (r_image) {
				cout << "Error: Image Save" << r_image << endl;
				r = FP_ENROLL_FAIL;
				break;
			} 
		}
				
		switch (r) {
			case FP_ENROLL_COMPLETE:
				cout << "Message: Enroll complete!" << endl;
				break;
			case FP_ENROLL_FAIL:
				cout << "Message: Enroll failed, something wen't wrong" << endl;
				break;
			case FP_ENROLL_PASS:
				cout << "Message: Enroll stage passed. Yay!" << endl;
				break;
			case FP_ENROLL_RETRY:
				cout << "Message: Didn't quite catch that. Please try again" << endl;
				break;
			case FP_ENROLL_RETRY_TOO_SHORT:
				cout << "Message: Your swipe was too short, please try again" << endl;
				break;
			case FP_ENROLL_RETRY_CENTER_FINGER:
				cout <<"Message: Didn't catch that, please center your finger on the sensor and try again" << endl;
				break;
			case FP_ENROLL_RETRY_REMOVE_FINGER:
				cout << "Message: Scan failed, please remove your finger and then try again." << endl;
				break;
		}
		

		if (r == FP_ENROLL_FAIL || r == FP_ENROLL_COMPLETE) {
			break;
		}
	}

	if (r != FP_ENROLL_COMPLETE) {
		fp_dev_close(dev);
		fp_exit();
		return 1;
	}
	
	r = fp_print_data_save(enrolled_print, person);
	if (r < 0) {
		cout <<"Error: Data Save" << endl;
		fp_dev_close(dev);
		fp_exit();
		return 1;
	}
	
	cout << "Success: Done!" << endl;
	fp_dev_close(dev);
	fp_exit();
	return 0;	
}

int run_identify() {
	int person = 55;
	int r = 1; 

	if (exists_file(finger_path_identify) == true) {
		string cmd = "rm \"" + string(finger_path_identify) + "\"";
		cout << "Message: Executing " << cmd << endl;
		system(cmd.c_str()); 
	}
	
	struct fp_dev* dev = initialize_fp();
	if (dev == NULL) {
		return 1;
	}
	
	// Loading element into list
	struct fp_img *img = NULL;
	int people_list[50];
	int index = 0;
	
	struct fp_print_data * print_gallery_temp[50];
	for(int i = 0; i < 50; i++) {
		struct fp_print_data *enrolled_print;
		int finger_code = i;
		r = fp_print_data_load(dev, finger_code, &enrolled_print);
		
		if (r == 0) {
			cout << "Validate!" << endl;
			print_gallery_temp[index] = enrolled_print;
			people_list[index] = i;
			index++;
		} else if (r != -2) {
			cout << "Error: Print data load error " << r << endl;	
			fp_dev_close(dev);
			fp_exit();
			return 1;
		}
	}
	
	// Avoid segmentation fault errors
	cout << "Message: idx " << index << endl;
	struct fp_print_data ** print_gallery = get_gallery_obj(index);
	for (int i = 0; i < index; i++) {
		print_gallery[i] = print_gallery_temp[i];
	}

	if (index == 0) {
		cout << "Error: No enrolled fingers" << endl;
		fp_dev_close(dev);
		fp_exit();
		return 1;
	}
	
	size_t offset;
	
	while(true) {
		cout << "Message: Put Finger" << endl;
		r = fp_identify_finger_img(dev, print_gallery, &offset, &img);
		
		cout << "Done!" << endl;
	
		if (img) {
			int r_image;
			char c_path[100];
			strcpy(c_path, finger_path_identify);
			r_image = fp_img_save_to_file(img, c_path);
				
			fp_img_free(img);
			
			if (r_image) {
				cout << "Error: Image Save" << r_image << endl;
				r = 1;
				break;
			} 
		}
		

		switch (r) {
			case FP_VERIFY_NO_MATCH:
				cout <<"Error: No Match" << endl;
				break;
			case FP_VERIFY_MATCH:
				cout <<"Success: Match " << people_list[offset] << endl;
				break;
			case FP_VERIFY_RETRY:
				cout <<"Message: Scan didn't quite work. Please try again" << endl;
				break;
			case FP_VERIFY_RETRY_TOO_SHORT:
				cout <<"Message: Swipe was too short, please try again" << endl;
				break;
			case FP_VERIFY_RETRY_CENTER_FINGER:
				cout <<"Message: Please center your finger on the sensor and try again" << endl;
				break;
			case FP_VERIFY_RETRY_REMOVE_FINGER:
				cout <<"Message: Please remove finger from the sensor and try again" << endl;
				break;
		}
		
		if (r == FP_VERIFY_NO_MATCH || r == FP_VERIFY_MATCH) {
			break;
		}
	}
	
	// Closing devices
	fp_dev_close(dev);
	fp_exit();
	
	if (r != 0) {
		return 1;
	}
	else {
		return 0;
	}
}

int run_verify(int person) {
	if (person < 0 || person >= 50) {
		cout << "Error: Invalid person: " << person << endl;
		return 1;
	}
	
	string route_finger = path_fprint + std::to_string(person);
	
	cout << route_finger << endl;
	if (exists_file(route_finger) == false) {
		cout << "Error: Person not enrolled: " << person << endl;
		return 1; 
	}
	
	int r = 1; 
	if (exists_file(finger_path_verify) == true) {
		string cmd = "rm \"" + string(finger_path_verify) + "\"";
		cout << "Message: Executing " << cmd << endl;
		system(cmd.c_str()); 
	}

	struct fp_dev* dev = initialize_fp();
	if (dev == NULL) {
		return 1;
	}
	
	// Loading element into list
	struct fp_img *img = NULL;

	struct fp_print_data *enrolled_print;
	int finger_code = person;
	r = fp_print_data_load(dev, finger_code, &enrolled_print);
	if (r < 0) {
		cout << "Error: Print data load error " << r << endl;	
		fp_dev_close(dev);
		fp_exit();
		return 1;
	}

	
	struct fp_print_data *print_gallery[1];
	print_gallery[0] = enrolled_print;
	
	size_t offset;
	
	while(true) {
		cout << "Message: Put Finger" << endl;
		r = fp_identify_finger_img(dev, print_gallery, &offset, &img);
	
		if (img) {
			int r_image;
			char c_path[100];
			strcpy(c_path, finger_path_verify);
			r_image = fp_img_save_to_file(img, c_path);
				
			fp_img_free(img);
			
			if (r_image) {
				cout << "Error: Image Save" << r_image << endl;
				r = 1;
				break;
			} 
		}

		switch (r) {
			case FP_VERIFY_NO_MATCH:
				cout <<"Error: No Match" << endl;
				break;
			case FP_VERIFY_MATCH:
				cout <<"Success: Match " << offset << endl;
				break;
			case FP_VERIFY_RETRY:
				cout <<"Message: Scan didn't quite work. Please try again" << endl;
				break;
			case FP_VERIFY_RETRY_TOO_SHORT:
				cout <<"Message: Swipe was too short, please try again" << endl;
				break;
			case FP_VERIFY_RETRY_CENTER_FINGER:
				cout <<"Message: Please center your finger on the sensor and try again" << endl;
				break;
			case FP_VERIFY_RETRY_REMOVE_FINGER:
				cout <<"Message: Please remove finger from the sensor and try again" << endl;
				break;
		}
		
		if (r == FP_VERIFY_NO_MATCH || r == FP_VERIFY_MATCH) {
			break;
		}
	}
	
	// Closing devices
	fp_dev_close(dev);
	fp_exit();
	
	if (r != 0) {
		return 1;
	}
	else {
		return 0;
	}
}

int run_unenroll(int person) {
	if (person < 0 || person >= 50) {
		cout << "Error: Invalid person: " << person << endl;
		return 1;
	}
	
	string route_finger = path_fprint + std::to_string(person);
	
	cout << route_finger << endl;
	if (exists_file(route_finger) == false) {
		cout << "Error: Person not enrolled: " << person << endl;
		return 1; 
	}
	
	if (remove(route_finger.c_str()) != 0) {
		cout << "Error: Deleting file " << route_finger << endl;
		return 1;
	}
		
	cout << "Success: Delete" << endl;
	return 0;
}

int run_delete() {
	if (exists_file(path_fprint) == true) {
		string cmd = "rm -r \"" + string(path_fprint) + "\"";
		cout << "Message: Executing " << cmd << endl;
		system(cmd.c_str()); 
	}
	
	cout << "Success: Folder deleted" << endl;
	return 0;
}


int main(int argc, char** argv) {
	if (argc < 2) {
		cout << "Usage: program -o [argument]" << endl;
		return 1;
	}
	if (strcmp(argv[1], "-c") == 0)  {
		return run_capture();
	}
	else if (strcmp(argv[1], "-e") == 0) {
		if (argc < 3) {
			cout << "Argument -e must have an argument" << endl;
			return 1;
		}
	
		int person = atoi(argv[2]);
		return run_enroll(person);
	} 
	else if (strcmp(argv[1], "-v") == 0) {
		if (argc < 3) {
			cout << "Argument -e must have an argument" << endl;
			return 1;
		}
		int person = atoi(argv[2]);
		return run_verify(person);
	}
	else if (strcmp(argv[1], "-i") == 0) {
		return run_identify();
	}
	else if (strcmp(argv[1], "-u") == 0) {
		if (argc < 3) {
			cout << "Argument -u must have an argument" << endl;
			return 1;
		}
		int person = atoi(argv[2]);
		return run_unenroll(person);
	}
	else if (strcmp(argv[1], "-d") == 0) {
		return run_delete();
	}
	else if (strcmp(argv[1], "-h") == 0) {
		cout << "Usage " << endl;
		cout << "-c: Capture a fingerprint" << endl;
		cout << "-e [number 0-49]: Enroll a fingerprint" << endl;
		cout << "-v [number 0-49]: Verify a fingerprint" << endl;
		cout << "-i: Identify a fingerprint" << endl;
		cout << "-u [number 0-49]: Unenroll a fingerprint" << endl;
		cout << "-d: Delete all fingerprints" << endl;
	}
	else {
		cout << "Unrecognized option: " << argv[1] << endl;
		return 1;
	}	
}