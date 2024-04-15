/**
 #  File name : CS112_A3_Part2B_S5,6_20230595_20230354_20230340.cpp
 #  Program : Tool for Image Processing and editing
 #  TA :: rana abdelkader >>> S6,5

 #           Name              |    ID     |   Filters id   |       Email
    ---------------------------|-----------|----------------|-----------------------
    Mohamed Khaled Gamal       | 20230595  | 3,6,9,12,14,15 | medo.kgm2018@gmail.com
    Mohamed Mahmoud Abdelbaset | 20230354  | 2,5,8,11,13,16 | mohamedmahmoud050505@gmail.com
    Mohamed Sherif Mohamed     | 20230340  | 1,4,7,10,17,18 | M07amedsherif2005@gmail.com
    --------------------------------------------------------------------------
 #  System diagram , Explain for the edditional cereative filters
    | Visit |->> https://drive.google.com/drive/folders/1VKaakWXMguWc4vztbF1bv7wOXsn_jrim?usp=sharing

 #  For Git hub
    | Visit |->> https://github.com/m07amedsherif/assignment-3
**/


#include <bits/stdc++.h>
#include "Image_Class.h"
using namespace std;
#define inRange(x,s,e) ( x >= s && x <= e )

string Main_filename,LAST = "Last_Version.jpg",CURRENT = "Work_Area.jpg";
// Common Function to get valid choice from specific values
string get_choice(bool is_range,vector<string>vec,auto output)
{
    string input = "NAN";
    if(is_range)
    {
        if(vec[0] == "i")
        {
            // int range
            input = to_string(stoll(vec[1])-1);
            while(!inRange( stoll(input) , stoll(vec[1]) , stoll(vec[2]) ))
            {
CIN_AGAIN_RANGING:;
                cout << output;
                cin >> input;
                for(int i = (input[0] == '-'); i < input.size(); i++)
                {
                    if( !inRange(input[i],'0','9') )
                    {
                        goto CIN_AGAIN_RANGING;
                    }
                }
            }
        }
        else
        {
            // string range
            input = vec[1];
            input[0]--;
            while(!inRange(input,vec[1],vec[2]))
            {
                cout << output;
                cin >> input;
            }
        }
    }
    else
    {
        auto it = find(vec.begin(), vec.end(), input);
        while(it == vec.end())
        {
            cout << output;
            cin >> input;
            it = find(vec.begin(), vec.end(), input);
        }
    }
    return input;
}

void get_My_image_file(string &file_name, bool is_exist)
{
CIN_FILE_AGN:;
cout << "Please enter your image name to Edit it: " << endl;
    cout << "The name must end with ('.png' , '.jpg' , '.tga' , '.bmp' ): ";
    file_name = "";
    while(file_name.size() == 0)
    {
        getline(cin,file_name);
    }
    if(file_name.size() < 5)
    {
        cout << "Invalid Name :(\n";
        goto CIN_FILE_AGN;
    }
    string extn = file_name.substr(file_name.size()-4);

    if(extn != ".png" &&
       extn != ".tga" &&
       extn != ".bmp" &&
       extn != ".jpg" ){
        cout << "Invalid Extension :(\n";
        goto CIN_FILE_AGN;
    }
    file_name.pop_back();
    file_name.pop_back();
    file_name.pop_back();
    file_name.pop_back();
    for(auto &c : file_name)
    {
        if(!inRange(c,'0','9') && !inRange(c,'A','Z') && !inRange(c,'a','z') && c != '_' && c != ' ' )
        {
            cout << "Invalid Name :(\n";
            goto CIN_FILE_AGN;
        }
    }
    if(is_exist)
    {
        file_name += extn;
        ifstream file(file_name.c_str());
        if( !file.good() )
        {
            cout << "No Such file :(\n";
            goto CIN_FILE_AGN;
        }
    }
}

void Save_Curr_Image(Image &My_image,string is_auto)
{
    if(is_auto != "user")
    {
        cout << "Something is processing please be calm..\n";
        My_image.saveImage(is_auto);
    }
    else
    {
        string filename = Main_filename;

        string input = get_choice(0,{"O","o","n","N"},"Do you want to save on the Old image or New one ? (o,n)::");

        if(input == "n" || input == "N")
        {
            get_My_image_file(filename,0);
        }
        cout << "Saving....\n";
        My_image.saveImage(filename);
        cout << "Saved!" << endl;
        system(filename.c_str());
    }
}

vector<int> GET_RGB_From_User()
{
    vector<int> RGB_Color(3,0);
    string input = get_choice(1,{"i","1","7"},
                       "Which Color you want?\n1) Red\n2) Blue\n3) Green\n4) Black\n5) White\n6) Randomly Picked by the Program\n7) Expert mode\nChoose ( 1 , 2 , 3 , 4 , 5 , 6 , 7 )::");

    if(input == "1")
    {
        RGB_Color[0] = 255;
    }
    else if(input == "2")
    {
        RGB_Color[1] = 255;
    }
    else if(input == "3")
    {
        RGB_Color[2] = 255;
    }
    else if(input == "4")
    {
        RGB_Color[0] = RGB_Color[1] = RGB_Color[2] = 0;
    }
    else if(input == "5")
    {
        RGB_Color[0] = RGB_Color[1] = RGB_Color[2] = 255;
    }
    else if(input == "7")
    {
        RGB_Color[0] = stoi(get_choice(1,{"i","0","255"},"*For Expert mode Amount of RED color? [ 0 ~ 255 ]::\n"));
        RGB_Color[1] = stoi(get_choice(1,{"i","0","255"},"**For Expert mode Amount of GREEN color? [ 0 ~ 255 ]::\n"));
        RGB_Color[2] = stoi(get_choice(1,{"i","0","255"},"***For Expert mode Amount of BLUE color? [ 0 ~ 255 ]::\n"));
    }
    else
    {
        // rand(0,255)
        srand(time(nullptr));
        RGB_Color[0] = rand() % 256;
        RGB_Color[1] = rand() % 256;
        RGB_Color[2] = rand() % 256;
    }
    return RGB_Color;
}

void Resize_Operator_11(Image& My_image,int width2 = -1,int height2 = -1,bool is_auto = false){
    if(!is_auto)
    {
REGET_DIMEN:;
        width2 = stoi(get_choice(1,{"i","20","10000"},"Enter Your Targeted Width [ 20 ~ 10'000 ] ::"));
        height2 = stoi(get_choice(1,{"i","20","10000"},"Enter Your Targeted height [ 20 ~ 10'000 ] ::"));
    }
    double w_ratio= (double)(My_image.width) / width2;
    double h_ratio = (double)(My_image.height) / height2;
    if ( !is_auto && (w_ratio < 0.5 || h_ratio < 0.5  || w_ratio > 1.5 || h_ratio > 1.5 )){
        cout << "Warning:" << endl;
        cout << "The new dimensions are significantly different from the original dimensions (Quality not as the Original)." << endl;
        string choice = get_choice(0,{"Y","n","y","N"},"Do you want to continue? (y,n):: ");
        if (choice == "n" || choice == "N"){
            cout << "Operation canceled by user." << endl;
            goto REGET_DIMEN;
        }
    }
    Image New_image(width2,height2);
    int res_W, res_H;
    int channels = New_image.channels;
    for (int i = 0; i < height2; i++){
        for (int j = 0; j < width2; j++) {
            res_H = floor(i * h_ratio);
            res_W = floor(j * w_ratio);
            for (int c = 0; c < channels; c++) {
                New_image(j,i,c) = My_image(res_W , res_H , c);
            }
        }
    }
    My_image = New_image;
}


void Filter_Grayscale_1(bool is_auto = 0)
{
    Image My_image(CURRENT);
    if(!is_auto)
    {
        Save_Curr_Image(My_image,LAST);
    }

    for (int i = 0; i < My_image.width; i++)
    {
        for (int j = 0; j < My_image.height; j++)
        {
            int average = 0;

            average = My_image(i, j, 0)*0.2989 + My_image(i, j, 1)*0.5870 +  My_image(i, j, 2)*0.1140;

            for (int rgb = 0; rgb < 3; rgb++)
            {
                My_image(i, j, rgb) = average;
            }
        }
    }

    Save_Curr_Image(My_image,CURRENT);
}
void Filter_Black_and_White_2(bool is_auto = 0)
{
    Image My_image(CURRENT);
    if(!is_auto)
    {
        Save_Curr_Image(My_image,LAST);
    }

    for (int i = 0; i < My_image.width; i++) {
        for (int j = 0; j < My_image.height; j++) {
            int avg = 0; // Initialize average value
            for (int k = 0; k < My_image.channels; k++) {
                avg += My_image(i, j, k); // Accumulate pixel values
            }

            // Set all channels to the average value
            int pix = (avg < 255) ? 0 : 255;
            for (int k = 0; k < My_image.channels; k++) {
                My_image(i, j, k) = pix;
            }
        }
    }

    Save_Curr_Image(My_image,CURRENT);
}
void Filter_Invert_3(bool is_auto = 0)
{
    Image My_image(CURRENT);
    if(!is_auto)
    {
        Save_Curr_Image(My_image,LAST);
    }

    for (int i = 0; i < My_image.width; i++)
    {
        for (int j = 0; j < My_image.height; j++)
        {
            for (int rgb = 0; rgb < 3; rgb++)
            {
                My_image(i, j, rgb) = 255 - My_image(i, j, rgb);
            }
        }
    }
    Save_Curr_Image(My_image,CURRENT);
}


void Filter_Merging_4(bool is_auto = 0)
{
    Image my_image1(CURRENT);
    if(!is_auto)
    {
        Save_Curr_Image(my_image1,LAST);
    }

    string image_name2;
    cout << "Your Second Image to merge with the original one ?\n";
    get_My_image_file(image_name2,1);

    Image my_image2(image_name2);
    string TO_PRINT = "";
    TO_PRINT += "Do you want to\n";
    TO_PRINT += "1)Upscale both to the largest dimensions\n";
    TO_PRINT += "2)Merge to the minimum dimensions\n";
    TO_PRINT += "Enter your choice (1,2) ::";
    string make_equal = get_choice(0,{"1","2"},TO_PRINT);

    if(make_equal == "1")
    {
        Resize_Operator_11(my_image1,max(my_image1.width,my_image2.width) , max(my_image1.height,my_image2.height) , 1);
        Resize_Operator_11(my_image2,max(my_image1.width,my_image2.width) , max(my_image1.height,my_image2.height) , 1);
    }
    int min_width = min(my_image1.width,my_image2.width);
    int min_height = min(my_image1.height,my_image2.height);

    Image new_image(min_width,min_height);

    for(int i = 0; i < new_image.width; ++i){
        for(int j = 0; j < new_image.height; ++j){
            for(int k = 0; k < 3; k++){
                int temp= (my_image1(i, j, k)+ my_image2(i, j, k))/2 ;
                new_image(i, j, k) = temp;
            }
        }
    }

    Save_Curr_Image(new_image,CURRENT);
}

void Filter_Flip_5(int is_auto = 0)
{
    Image My_image(CURRENT);
    if(!is_auto)
    {
        Save_Curr_Image(My_image,LAST);
    }

    string input = "";
    if(!is_auto)
    {
        input = get_choice(0,{"H","V","v","h"},"Flip Horizontal or Vertical ? (V,H) ::");
    }
    if(input == "H" || input == "h" || is_auto == 1 || is_auto == 3)
    {
        for (int i = 0; i < My_image.height; i++) {
            for (int j = 0; j < My_image.width / 2; j++) {
                for (int k = 0; k < My_image.channels; k++) {
                    unsigned char temp = My_image.getPixel(j, i, k);
                    My_image.setPixel(j, i, k, My_image.getPixel(My_image.width - 1 - j, i, k));
                    My_image.setPixel(My_image.width - 1 - j, i, k, temp);
                }
            }
        }
    }
    if(input == "V" || input == "v" || is_auto == 2 || is_auto == 3)
    {
        for (int i = 0; i < My_image.width; i++) {
            for (int j = 0; j < My_image.height / 2; j++) {
                for (int k = 0; k < My_image.channels; k++) {
                    unsigned char temp = My_image.getPixel(i, j, k);
                    My_image.setPixel(i, j, k, My_image.getPixel(i, My_image.height - 1 - j, k));
                    My_image.setPixel( i, My_image.height - 1 - j, k, temp);
                }
            }
        }
    }
    Save_Curr_Image(My_image,CURRENT);
}

void Filter_Rotate_6(bool is_auto = 0)
{
    Image My_image(CURRENT);
    if(!is_auto)
    {
        Save_Curr_Image(My_image,LAST);
    }
    int angel = stoi( get_choice(0,{"90","180","270"},"Rotation degree ? ( 90 , 180 , 270 )::\n") );
    if(angel == 180)
    {
        Filter_Flip_5(3);
    }
    else if(angel == 90)
    {
        Filter_Flip_5(2);
    }
    else if(angel == 270)
    {
        Filter_Flip_5(1);
    }
    if(angel != 180)
    {
        Image Temp_image(My_image.height, My_image.width);
        for (int i = 0; i < My_image.width; i++)
        {
            for (int j = 0; j < My_image.height; j++)
            {
                for (int rgb = 0; rgb < 3; rgb++)
                {
                    Temp_image(j, i, rgb) = My_image(i, j, rgb);
                }
            }
        }
        Save_Curr_Image(Temp_image,CURRENT);
    }
}


void Filter_Brightness_7(bool is_auto = 0)
{
    Image My_image(CURRENT);
    if(!is_auto)
    {
        Save_Curr_Image(My_image,LAST);
    }

    string input = get_choice(0,{"D","B","d","b"},"Darker or Brighter? (D/B)::\n");
    string strn = get_choice(0,{"25","50","75","25%","50%","75%"},"Strength ? ( 25% , 50% , 75% )::\n");
    double factor = 1;
    if(input == "D" || input == "d")
    {
        if(strn == "25" || strn == "25%")
        {
            factor = 0.75;
        }
        else if(strn == "50" || strn == "50%")
        {
            factor = 0.5;
        }
        else
        {
            factor = 0.25;
        }
    }
    else
    {
        if(strn == "25" || strn == "25%")
        {
            factor = 1.25;
        }
        else if(strn == "50" || strn == "50%")
        {
            factor = 1.5;
        }
        else
        {
            factor = 1.75;
        }
    }

    // Apply lightening to each pixel
    for (int i = 0; i < My_image.width; ++i)
    {
        for (int j = 0; j < My_image.height; ++j)
        {
            for (int k = 0; k < My_image.channels; ++k)
            {
                int tmp = My_image(i, j, k);
                tmp = min(255.0,tmp*factor);
                My_image(i, j, k) = int(tmp);
            }
        }
    }
    Save_Curr_Image(My_image,CURRENT);
}

void Filter_Crop_8(bool is_auto = 0)
{
    Image My_image(CURRENT);
    if(!is_auto)
    {
        Save_Curr_Image(My_image,LAST);
    }

    int w = stoi(get_choice(1,{"i","10",to_string(My_image.width)},"*Enter width? [ 10 ~ " + to_string(My_image.width) + " ] ::"));
    int h = stoi(get_choice(1,{"i","10",to_string(My_image.height)},"**Enter height? [ 10 ~ " + to_string(My_image.height) + " ] ::"));

    int start_i = (My_image.width - w)/2;

    Image Cropped_image(w,h);

    for (int i = 0; i < w; i++)
    {
        int start_j = (My_image.height - h)/2;
        for (int j = 0; j < h; j++)
        {
            for (int rgb = 0; rgb < 3; rgb++)
            {
                Cropped_image(i, j, rgb) = My_image(start_i, start_j, rgb);
            }
            start_j++;
        }
        start_i++;
    }

    Save_Curr_Image(Cropped_image,CURRENT);
}

void Filter_Frame_9(bool is_auto = 0)
{
    Image My_image(CURRENT);
    if(!is_auto)
    {
        Save_Curr_Image(My_image,LAST);
    }

    string input = get_choice(0,{"L","l","S","s","M","m"},"Frame thickness small,medium,large? ( S , M , L )::");

    float factor = 0.12;
    if(input == "M" || input == "m")
    {
        factor = 0.07;
    }
    else if(input == "S" || input == "s")
    {
        factor = 0.03;
    }
    string TO_PRINT = "\n";
    TO_PRINT += "Do you want to\n";
    TO_PRINT += "1) Add a simple Frame\n";
    TO_PRINT += "2) Add an advanced Frame\n";
    TO_PRINT += "Enter your choice (1) ::";

    string make_advanced = get_choice(0,{"1","2"},TO_PRINT);

    vector<int> FrameColor = GET_RGB_From_User();
    int thick = min(My_image.width,My_image.height)*factor;
    Image New_image(My_image.width+thick*2,My_image.height+thick*2);
    for (int i = 0; i < New_image.width; i++)
    {
        for (int j = 0; j < New_image.height; j++)
        {
            for (int rgb = 0; rgb < 3; rgb++)
            {
                if( inRange(i-thick,0,My_image.width-1) && inRange(j-thick,0,My_image.height-1) )
                {
                    New_image(i, j, rgb) = My_image(i-thick, j-thick, rgb);
                }
                else
                {
                     New_image(i, j, rgb) = FrameColor[rgb];
                }
            }
        }
    }
    if(make_advanced == "2")
    {
        string input = get_choice(0,{"Y","y","N","n"},"Do you want to mix a new second color ?(y,n) ::");
        if(input == "Y" || input == "y")
        {
            cout << "Now Enter your second color for Fancy frame :\n";
            FrameColor = GET_RGB_From_User();
        }
        input = get_choice(0,{"Y","y","N","n"},"Do you want to mix a new third color ?(y,n) ::");
        vector<int> FrameColor2 = FrameColor;
        if(input == "Y" || input == "y")
        {
            cout << "Now Enter your second color for Fancy frame :\n";
            FrameColor2 = GET_RGB_From_User();
        }
        for (int i = thick*1.4; i < thick*1.6; i++)
        {
            for (int j = 0; j < New_image.height; j++)
            {
                for (int rgb = 0; rgb < 3; rgb++)
                {
                    New_image(i, j, rgb) = FrameColor[rgb];
                    New_image(New_image.width-i, j, rgb) = FrameColor2[rgb];
                }
            }
        }
        for (int i = 0; i < New_image.width; i++)
        {
            for (int j = thick*1.4; j < thick*1.6; j++)
            {
                for (int rgb = 0; rgb < 3; rgb++)
                {
                    New_image(i, j, rgb) = FrameColor[rgb];
                    New_image(i, New_image.height-j, rgb) = FrameColor2[rgb];
                }
            }
        }
    }
    Save_Curr_Image(New_image,CURRENT);
}
void Filter_Edge_Detector_10(bool is_auto = 0)
{
    Filter_Black_and_White_2(1);
    Image My_image(CURRENT);
    if(!is_auto)
    {
        Save_Curr_Image(My_image,LAST);
    }
    int thick = ( min(My_image.width, My_image.height) + 199 /200 );
    for (int i = 0; i < My_image.width-thick; i++)
    {
        for (int j = 0; j < My_image.height-thick; j++)
        {
            if (My_image(i + 1, j, 0) != My_image(i, j + 1, 0) ||
                My_image(i, j, 0)     != My_image(i, j + 1, 0)  )
            {
                j = j + thick - 1;
                for (int jj =  j; jj <= j; jj++)
                {
                    My_image(i, jj, 0) = My_image(i, jj, 1) = My_image(i, jj, 2) = 0;
                }
            }
            else
            {
                My_image(i, j, 0) = My_image(i, j, 1) =  My_image(i, j, 2) = 255;
            }
        }
    }
    Save_Curr_Image(My_image,CURRENT);
}

void Filter_Resize_11(bool is_auto = 0)
{
    Image My_image(CURRENT);
    if(!is_auto)
    {
        Save_Curr_Image(My_image,LAST);
    }
    Resize_Operator_11(My_image);
    Save_Curr_Image(My_image,CURRENT);
}

void Filter_Blur_12(bool is_auto = 0)
{
    Image My_image(CURRENT);
    if(!is_auto)
    {
        Save_Curr_Image(My_image,LAST);
    }
    string input = get_choice(0,{"25","50","75","25%","50%","75%"},"Blur strength ? ( 25% , 50% , 75% )::\n");
    int strength = (input[0] == '2' ? 5 : (input[0] == '5' ? 10 : 15) );

    long double Time = strength;
    Time = Time*Time*My_image.width*My_image.height/3333333;
    cout << "The time reduced from ";

    if(Time/60 > 2)
    {
        cout << "[ " << Time/60/2 << " ~ " << 1.2*Time/60 << " ]";
        cout << " Minutes";
    }
    else
    {
        cout << "[ " << Time/2 << " ~ " << 1.2*Time << " ]";
        cout << " Seconds";
    }
    cout << " to " << Time / strength / strength * 2.1 << " Seconds due to using Dynamic Programming (dp)\n";


    vector<vector<vector<long long>>> dp(My_image.width+1,vector<vector<long long>>(My_image.height+1,vector<long long>(3)));
    Image New_image(My_image.width,My_image.height);
    for (int i = 1; i <= My_image.width; i++)
    {
        for (int j = 1; j <= My_image.height; j++)
        {
            for (int rgb = 0; rgb < 3; rgb++)
            {
                dp[i][j][rgb] = My_image(i-1, j-1, rgb) + dp[i-1][j][rgb] + dp[i][j-1][rgb] - dp[i-1][j-1][rgb];
            }
        }
    }
    for (int i = 0; i < My_image.width; i++)
    {
        for (int j = 0; j < My_image.height; j++)
        {

            long long Sums[3] = {0,0,0};
            int total_pixels = 0;

            for (int rgb = 0; rgb < 3; rgb++)
            {
                Sums[rgb] += dp[ min( My_image.width , i + strength ) ][ min( My_image.height , j + strength ) ][ rgb ];
                Sums[rgb] -= dp[ min( My_image.width , i + strength ) ][ max( 0               , j - strength ) ][ rgb ];
                Sums[rgb] -= dp[ max( 0              , i - strength ) ][ min( My_image.height , j + strength ) ][ rgb ];
                Sums[rgb] += dp[ max( 0              , i - strength ) ][ max( 0               , j - strength ) ][ rgb ];
            }

            total_pixels  = min( My_image.height , j + strength ) - max( 0 , j - strength );
            total_pixels *= min( My_image.width  , i + strength ) - max( 0 , i - strength );

            for (int rgb = 0; rgb < 3; rgb++)
            {
                New_image(i, j, rgb) = Sums[rgb]/total_pixels;
            }
        }
    }
    Save_Curr_Image(New_image,CURRENT);
}

void Filter_Sunlight_13(bool is_auto = 0)
{
    Image My_image(CURRENT);
    if(!is_auto)
    {
        Save_Curr_Image(My_image,LAST);
    }
    for (int i = 0; i < My_image.width; i++)
    {
        for (int j = 0; j < My_image.height; j++)
        {
            My_image(i, j, 0) = min( 255 , My_image(i,j,0) + 40 );
            My_image(i, j, 1) = min( 255 , My_image(i,j,1) + 30 );
            My_image(i, j, 2) = max( 0   , My_image(i,j,2) - 50 );
        }
    }
    Save_Curr_Image(My_image,CURRENT);
}

void Filter_Oil_14(bool is_auto = 0)
{
    Image My_image(CURRENT);
    if(!is_auto)
    {
        Save_Curr_Image(My_image,LAST);
    }
    Image New_image(CURRENT);
    int R = 5,L = 20;
    long double Time = R;
    Time = Time*Time*My_image.width*My_image.height/3333333;
    cout << "This may take ";

    if(Time/60 > 2)
    {
        cout << "[ " << Time/60/2 << " ~ " << 1.2*Time/60 << " ]";
        cout << " Minutes";
    }
    else
    {
        cout << "[ " << Time/2 << " ~ " << 1.2*Time << " ]";
        cout << " Seconds";
    }

    for (int i = R; i < My_image.width - R; i++)
    {
        for (int j = R; j < My_image.height - R; j++)
        {
            int Intensity[256] = {0};
            long long sums[3][256] = {0};
            for (int di = i-R; di < i+R; di++)
            {
                for (int dj = j-R; dj < j+R; dj++)
                {
                    int col[3];
                    for (int rgb = 0; rgb < My_image.channels; rgb++)
                    {
                        col[rgb] = My_image(di, dj, rgb);
                    }
                    int I = min( 255 , ((col[0] + col[1] + col[2])/3 * L) / 255 );
                    Intensity[I]++;
                    for (int rgb = 0; rgb < My_image.channels; rgb++)
                    {
                        sums[rgb][I] += col[rgb];
                    }
                }
            }
            int mx = 0;
            int mxpos = 0;
            for( int nI = 0; nI < 256; nI++)
            {
                if( Intensity[nI] > mx )
                {
                    mx = Intensity[nI];
                    mxpos = nI;
                }
            }
            for (int rgb = 0; rgb < My_image.channels; rgb++)
            {
                New_image(i,j,rgb) = sums[rgb][mxpos] / mx;
            }
        }
    }
    Save_Curr_Image(New_image,CURRENT);
}



void Filter_Old_TV_15(bool is_auto = 0)
{
    Image My_image(CURRENT);
    if(!is_auto)
    {
        Save_Curr_Image(My_image,LAST);
    }
    int I = stoi(get_choice(1,{"i","1","5"},"Enter the intensity level you want [ 1 ~ 5 ] (Higher intensity takes more time)::"));
    for (int i = 0; i < My_image.width; i=i+I+1)
    {
        for (int j = 0; j < My_image.height; j=j+I+1)
        {
            for (int rgb = 0; rgb < My_image.channels; rgb++)
            {
                for (int di = 0; di < I; di++)
                {
                    int f = 15 + rand()%36;
                    for (int dj = 0; dj < I; dj++)
                    {
                        if( (i+j)%2 )
                        {
                            My_image(i+di, j+dj, rgb) = max(My_image(i+di, j+dj, rgb) - f, 0);
                        }
                        else
                        {
                            My_image(i+di, j+dj, rgb) = min(My_image(i+di, j+dj, rgb) + f, 255);
                        }
                    }
                }

            }
        }
    }
    Save_Curr_Image(My_image,CURRENT);
}

void Filter_Purple_16(bool is_auto = 0)
{
    Image My_image(CURRENT);
    if(!is_auto)
    {
        Save_Curr_Image(My_image,LAST);
    }
    for (int i = 0; i < My_image.width; i++)
    {
        for (int j = 0; j < My_image.height; j++)
        {
            My_image(i, j, 0) = min( 255 , int( My_image(i,j,0)*1.25 ) );
            My_image(i, j, 1) = min( 255 , int( My_image(i,j,1)*0.75 ) );
            My_image(i, j, 2) = min( 255 , int( My_image(i,j,2)*1.25 ) );
        }
    }
    Save_Curr_Image(My_image,CURRENT);
}

void Filter_Infrared_17(bool is_auto = 0)
{
    Image My_image(CURRENT);
    if(!is_auto)
    {
        Save_Curr_Image(My_image,LAST);
    }
    for (int i = 0; i < My_image.width; i++)
    {
        for (int j = 0; j < My_image.height; j++)
        {
            int green = 255 - My_image(i,j,2);
            int blue = 255 - My_image(i,j,1);

            My_image.setPixel(i, j, 0 ,255);
            My_image.setPixel(i, j, 1 ,green);
            My_image.setPixel(i, j, 2 ,blue);
        }
    }
    Save_Curr_Image(My_image,CURRENT);
}

void Filter_Skew_18(bool is_auto = 0)
{
    Image My_image(CURRENT);
    if(!is_auto)
    {
        Save_Curr_Image(My_image,LAST);
    }
    int W = My_image.width;
    int H = My_image.height;


    double angle = stoi(get_choice(1,{"i","-75","75"},"Enter angle you want [ -75 ~ 75 ] deg ::"));

    bool is_back = (angle < 0);
    angle = abs(angle);

    const double PI = 3.141592653589793238462643383279502884197;
    angle = angle / 180 * PI;

    double tangent = tan(angle);
    Image New_image( tangent * H + W + 1 , H );

    for (int i = 0; i < H; i++)
    {
        int Shift = abs(H * tangent * (is_back) - (H - i) * tangent);
        for (int j = Shift; j < Shift + W; j++)
        {
            for (int c = 0; c < My_image.channels; c++)
            {
               New_image(j, i, c) = My_image(j - Shift, i, c);
            }
        }
    }
    Save_Curr_Image(New_image,CURRENT);
}

void Filter_Fill_Color_Additional(bool is_auto = 0)
{
    Image My_image(CURRENT);
    if(!is_auto)
    {
        Save_Curr_Image(My_image,LAST);
    }

    vector<int> FillColor = GET_RGB_From_User();

    for (int i = 0; i < My_image.width; i++)
    {
        for (int j = 0; j < My_image.height; j++)
        {
            for (int rgb = 0; rgb < 3; rgb++)
            {
                My_image(i, j, rgb) = FillColor[rgb];
            }
        }
    }

    Save_Curr_Image(My_image,CURRENT);
}

void Filter_Ghost_Additional(bool is_auto = 0)
{
    Image image(CURRENT);
    if(!is_auto)
    {
        Save_Curr_Image(image,LAST);
    }
    int value = 1;

    string out = "Please choose the value of difference between pixels\n";
    out += "NOTICE THAT : The more pixels the photo has or the more big the photo is means the bigger value you have to choose\n";
    out += "[1]- Very Low\n";
    out += "[2]- Low\n";
    out += "[3]- Meddium\n";
    out += "[4]- High\n";
    out += "[5]- Recommended\n";
    out += "Your decision is : ";

    string s = get_choice(0,{"1","2","3","4","5"},out);

    if (s == "1"){value = image.width*0.005;}
    else if(s == "2"){value = image.width*0.015;}
    else if (s == "4"){value = image.width*0.05;}
    else{value = image.width*0.03;}

    for (int i = 0; i < image.width - value; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            for(int k = 0 ; k < 3 ; k++)
            {
                image(i , j ,k) = (image(i + value ,j ,k)+ image(i , j  , k)) / 2;
            }
        }
    }
    Save_Curr_Image(image,CURRENT);
}


void Filter_ModernGold_Additional(bool is_auto = 0)
{
    Image image(CURRENT);
    if(!is_auto)
    {
        Save_Curr_Image(image,LAST);
    }
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int blue = 0.9 * image(i,j,2);
             blue = min(blue , 255);
            int green = 1.1 * image(i,j,1);
             green = min(green , 255);
            int red = 1.5 * image(i,j,0);
             red = min(red , 255);

            image.setPixel(i, j, 0 ,red);
            image.setPixel(i, j, 1 ,green);
            image.setPixel(i, j, 2 ,blue);
        }
    }
    Save_Curr_Image(image,CURRENT);
}


void Filter_Cold_Blue_Additional(bool is_auto = 0)
{
    Image image(CURRENT);
    if(!is_auto)
    {
        Save_Curr_Image(image,LAST);
    }
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int blue = 1.1 * image(i,j,2);
             blue = min(blue , 255);
            int green = 1.5 * image(i,j,1);
             green = min(green , 255);
            int red = 1.5 * image(i,j,0);
             red = min(red , 255);

            image.setPixel(i, j, 0 ,red/2);
            image.setPixel(i, j, 1 ,green/2);
            image.setPixel(i, j, 2 ,blue);
        }
    }
    Save_Curr_Image(image,CURRENT);
}

void Save_User_Choice(string vORIGIN,string vLAST,string vCURRENT)
{
    string input;
    cin >> input;
    input = get_choice(0,{"1","2","3"},
            "Which version do you want to save?\n1- Current Filtered Image\n2-Last Version\n3- Original Image\nChoose (1,2,3)::");
    if(input == "1")
    {
        input = vCURRENT;
    }
    else if(input == "2")
    {
        input = vLAST;
    }
    else
    {
        input = vORIGIN;
    }
    Image Resulted_image(input);
    Save_Curr_Image(Resulted_image,"user");
    system(input.c_str());
}

void Filters_Menu()
{
    string Status = "";
    bool can_undo = false;
    while(Status != "End")
    {
        string TOPRINT = "";
        TOPRINT += "\n\n\n";
        TOPRINT += "\nMain Filters :\n";
        TOPRINT += "------------------------------\n";
        TOPRINT += "1) Grayscale Filter                       2)  Black and White Filter       3)  Invert Filter \n";
        TOPRINT += "4) Merge Filter (Requires another image)  5)  Flip Filter                  6)  Rotate Filter \n";
        TOPRINT += "7) Darken and Lighten Filter              8)  Crop Filter                  9)  Adding a Frame Filter \n";
        TOPRINT += "10) Detect Edges Filter                   11) Resizing Filter              12) Blur Filter \n";

        TOPRINT += "\nBonus Filters :\n";
        TOPRINT += "------------------------------\n";
        TOPRINT += "13) Sunlight Filter                       14) Oil painting Filter          15) Old TV Filter \n";
        TOPRINT += "16) Purple Filter                         17) Infrared Filter              18) Skewing Filter \n";

        TOPRINT += "\nCreativity  Filters :\n";
        TOPRINT += "------------------------------\n";
        TOPRINT += "19) Fill with colors Filter               20) Ghost Filter                 21) Modern Gold Filter \n";
        TOPRINT += "22) Cold Blue Filter \n";

        TOPRINT += "\nOptions :\n";
        TOPRINT += "------------------------------\n";
        TOPRINT += "23) Preview Current photo \n";
        TOPRINT += "24) Undo Last Filter (at most one time) \n";
        TOPRINT += "25) Save the Current Version \n";
        TOPRINT += "26) Restore the original Image \n";
        TOPRINT += "27) End Editing \n";

        TOPRINT += "Enter Your choice a number from [ 1 ~ 26 ] ::";
        Status = get_choice(1,{"i","1","27"},TOPRINT);

        if(Status == "1")
        {
            Filter_Grayscale_1();
            can_undo = true;
        }
        else if(Status == "2")
        {
            Filter_Black_and_White_2();
            can_undo = true;
        }
        else if(Status == "3")
        {
            Filter_Invert_3();
            can_undo = true;
        }
        else if(Status == "4")
        {
            Filter_Merging_4();
            can_undo = true;
        }
        else if(Status == "5")
        {
            Filter_Flip_5();
            can_undo = true;
        }
        else if(Status == "6")
        {
            Filter_Rotate_6();
            can_undo = true;
        }
        else if(Status == "7")
        {
            Filter_Brightness_7();
            can_undo = true;
        }
        else if(Status == "8")
        {
            Filter_Crop_8();
            can_undo = true;
        }
        else if(Status == "9")
        {
            Filter_Frame_9();
            can_undo = true;
        }
        else if(Status == "10")
        {
            Filter_Edge_Detector_10();
            can_undo = true;
        }
        else if(Status == "11")
        {
            Filter_Resize_11();
            can_undo = true;
        }
        else if(Status == "12")
        {
            Filter_Blur_12();
            can_undo = true;
        }
        else if(Status == "13")
        {
            Filter_Sunlight_13();
            can_undo = true;
        }
        else if(Status == "14")
        {
            Filter_Oil_14();
            can_undo = true;
        }
        else if(Status == "15")
        {
            Filter_Old_TV_15();
            can_undo = true;
        }
        else if(Status == "16")
        {
            Filter_Purple_16();
            can_undo = true;
        }
        else if(Status == "17")
        {
            Filter_Infrared_17();
            can_undo = true;
        }
        else if(Status == "18")
        {
            Filter_Skew_18();
            can_undo = true;
        }
        else if(Status == "19")
        {
            Filter_Fill_Color_Additional();
        }
        else if(Status == "20")
        {
            Filter_Ghost_Additional();
        }
        else if(Status == "21")
        {
            Filter_ModernGold_Additional();
        }
        else if(Status == "22")
        {
            Filter_Cold_Blue_Additional();
        }
        else if(Status == "22")
        {
            system(CURRENT.c_str());
        }
        else if(Status == "24")
        {
            if(can_undo)
            {
                Image Temp1_image(LAST);
                Save_Curr_Image(Temp1_image,CURRENT);
            }
            else
            {
                cout << "Sorry but You can undo at most one time :(\n";
            }
            can_undo = false;
        }
        else if(Status == "25")
        {
            Image Resulted_image(CURRENT);
            Save_Curr_Image(Resulted_image,"user");
        }
        else if(Status == "26")
        {
            Image Temp1_image(Main_filename);
            Save_Curr_Image(Temp1_image,LAST);
            Save_Curr_Image(Temp1_image,CURRENT);
            cout << "Original Image Resroted!\n";
        }
        else if(Status == "27")
        {
            string save_before_quit = get_choice(0,{"Y","y","N","n"},"You are about to exit, would you like to save your work?\nEnter Your choice (Y,N)");
            if(save_before_quit == "Y" || save_before_quit == "y")
            {
                Image Resulted_image(CURRENT);
                Save_Curr_Image(Resulted_image,"user");
            }
            Status = "End";
        }
    }
}

void Start_Program()
{
    string Status = "";
    while(Status != "Back")
    {
        Status = get_choice(0,{"1","2","3"},"1) Open Current Existing Image \n2) Create Empty Image\n3) Back\nEnter Your Choice (1,2,3) ::");

        if(Status == "1")
        {
            Main_filename = "T2.jpg";
            get_My_image_file(Main_filename,1);
            Image Temp1_image(Main_filename);
            Save_Curr_Image(Temp1_image,LAST);
            Save_Curr_Image(Temp1_image,CURRENT);
            Filters_Menu();
        }
        else if(Status == "2")
        {
            get_My_image_file(Main_filename,0);
            int wid = stoi(get_choice(1,{"i","500","4000"},"*Enter the width you want to create the image with\n*Enter Your Choice [ 500 ~ 4000 ] ::"));
            int hig = stoi(get_choice(1,{"i","500","4000"},"**Enter the hight you want to create the image with\n**Enter Your Choice [ 500 ~ 4000 ] ::"));
            Image Temp1_image(wid,hig);
            Save_Curr_Image(Temp1_image,LAST);
            Save_Curr_Image(Temp1_image,CURRENT);
            Filter_Fill_Color_Additional();
            Filters_Menu();
        }
        else
        {
            Status = "Back";
        }
    }
}


int main()
{
    cout << "Welcome to the best Copy of photoshop !" << endl;
    string Status = "To Start";
    while(Status != "Exit")
    {
        Status = get_choice(0,{"1","2"},"1) Start Editing \n2) Exit\nEnter Your Choice (1,2) ::");

        if(Status == "1")
        {
            Start_Program();
        }
        else
        {
            Status = "Exit";
            cout << "Good Bye :(" << endl;
        }
    }
    return 0;
}
