var state = ["Alabama","Alaska","Arizona","Arkansas","California",
"Colorado","Connecticut","Delaware","Florida","Georgia",
"Hawaii","Idaho","Illinois","Indiana","Iowa",
"Kansas","Kentucky","Louisiana","Maine","Maryland",
"Massachusetts","Michigan","Minnesota","Mississippi","Missouri",
"Montana","Nebraska","Nevada","New Hampshire","New Jersey",
"New Mexico","New York","North Carolina","North Dakota","Ohio",
"Oklahoma","Oregon","Pennsylvania","Rhode Island","South Carolina",
"South Dakota","Tennessee","Texas","Utah","Vermont",
"Virginia","Washington","WestVirginia","Wisconsin","Wyoming"];
var height=[2.291288,3.834058,3.929377,6.236986,6.637771,7.355270,8.027453,
8.537564,10.860018,11.456439,12.424975,12.614278,12.775367,13.044922,
13.297368,13.349157,13.896043,14.501034,15.407790,15.454449,15.630099,
15.890249,16.976749,18.264994,19.437592,19.904271,21.167192,22.366046,
22.766642,24.894377,25.093027,28.635118,29.250641,31.477135,31.620405,
32.718802,36.734861,36.847931,38.527912,41.487950,48.725148,53.593376,
57.271022,64.993615,68.762272,87.326342,102.861557,168.611417,293.622751];
var merge =[
[-15,-29],
[-17,-26],
[-14,-16],
[-13,-32],
[-35,-44],
[-36,-46],
[-7,-38],
[-19,-41],
[-49,1],
[-21,-30],
[-37,6],
[-4,-42],
[-48,8],
[-34,-45],
[-22,-28],
[-27,2],
[-3,-31],
[-6,-43],
[-12,3],
[-1,-18],
[-50,11],
[-20,17],
[-8,20],
[5,7],
[-23,9],
[16,19],
[-24,-40],
[4,15],
[-47,10],
[-25,12],
[-10,18],
[-2,27],
[21,29],
[24,26],
[-11,25],
[-5,28],
[30,31],
[-39,33],
[-9,-33],
[13,14],
[23,32],
[22,36],
[35,40],
[41,42],
[37,38],
[34,43],
[39,44],
[45,46],
[47,48]];
function progress(){
	var dis = document.form.dis.value;
	var target = document.form.target.value;
	var output="";


    /*----------------- Your Code Start-------------*/

	 var i = 0;
	for(;i < state.length;i++)
	{
		if(state[i] == target)
		break;
	}
	i++;
	output = find(dis,i,output);
    var x = output.split(",");
	x.sort();
	output = x;

    /*----------------- Your Code End --------------*/
    document.getElementById('out').innerHTML= output;
}

function find(n, i, output)
{
 var j = 0;
 for(;j < merge.length;j++)
 {
  if(merge[j][0] == -i && merge[j][1] < 0)
  {
   output = state[0 - 1 - merge[j][1]];
   output = up(n, j + 1, output, 1);
   return output;
  }
  else if(merge[j][1] == -i && merge[j][0] < 0)
  {
   output = state[0 - 1 - merge[j][0]];
   output = up(n, j + 1, output, 1);
   return output;
  }
  else if(merge[j][1] == -i && merge[j][0] > 0)
  {
   output = down(n, merge[j][0] - 1, output, 1);
   output = up(n, j + 1, output, 1);
   return output;
  }
  else if(merge[j][0] == -i && merge[j][1] > 0)
  {
   output = down(n, merge[j][1] - 1, output, 1);
   output = up(n, j + 1, output, 1);
   return output;
  }
 }
}

function down(n, j, output, t)
{
 if(t > n)	//如果n=2則跳出
  return output;
 if(merge[j][0] > 0 && merge[j][1] > 0)
 {
  output = down(n, merge[j][0] - 1, output, t + 1);
  output = down(n, merge[j][1] - 1, output, t + 1);
  return output;
 }
 else if(merge[j][0] < 0 && merge[j][1] > 0)
 {
  output += state[0 - 1 - merge[j][0]];
  return down(n, merge[j][1] - 1, output, t + 1);
 }
 else if(merge[j][0] > 0 && merge[j][1] < 0)
 {
  output += state[0 - 1 - merge[j][1]];
  return down(n, merge[j][0] - 1, output, t + 1);
 }
 else if(merge[j][0] < 0 && merge[j][1] < 0)
 {
  output += state[0 - 1 - merge[j][0]];
  output += ","+state[0 - 1 - merge[j][1]];
  return output;
 }
}

function up(n, j, output, t)
{
 if(t > n)	//如果n=2則跳出
  return output;
 if(height[j-1] >= 50)	//如果高度超過50則跳出
  return output;
 for(var i =0;i < merge.length;i++)	//用for迴圈來找符合目標州上面的州
 {
  if(merge[i][0] == j && merge[i][1] < 0)	//輸出第一州名
  {
   output += ","+state[0 - 1 - merge[i][1]];
   return up(n, i + 1, output, t + 1);
  }
  else if(merge[i][1] == j && merge[i][0] < 0)	//輸出第二州名
  {
   output += ","+state[0 - 1 - merge[i][0]];
   return up(n, i + 1, output, t + 1);
  }
  else if(merge[i][0] == j && merge[i][1] > 0)	//合併階段
  {
   if(height[i] >= 50)//高度不能超過50
    return output;
   else	//計算高度50以下的州
   {
    output = up(n, i + 1, output, t + 1);
    output = down(n, merge[i][1] - 1, output, t + 1);
    return output;
   }
  }
  else if(merge[i][1] == j && merge[i][0] > 0)	//合併階段
  {
   if(height[i] >= 50)//高度不能超過50
    return output;
   else	//計算高度50以下的州
   {
    output = up(n, i + 1, output, t + 1);
    output = down(n, merge[i][0] - 1, output, t + 1);
    return output;
   }
  }
 }
}
