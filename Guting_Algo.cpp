/******************************************************************************
Anurag Sidharth Aribandi 2018A7PS1218H
Anish Sai Mitta 2018A7PS1221H
Himnish Kapoor 2018A7PS1215H
Varun Narayanan 2018A7PS1226H
*******************************************************************************/
#include <bits/stdc++.h>
using namespace std;

typedef struct ctree
{
    float x;
    string side;
    ctree* lson;
    ctree* rson;
}ctree;
///Class for the coordinate of a point
class Coordinate
{
public:
    float val;
    Coordinate()
    {
    	val = 0;
    }
    Coordinate(float v)
    {
        val = v;
    }
    bool operator < (Coordinate other) const
    {
        bool b= (val<other.val);
        return b;
    }
};
///Class for an Interval consisting of two coordinates
class Intrvl
{
public:
    mutable Coordinate bottom;
    mutable Coordinate top;
    int rect_no;
    Intrvl()
    {
       bottom = Coordinate(0);
       top =  Coordinate(0);
       rect_no = 0;
    }
    Intrvl(Coordinate b,Coordinate t,int x)
    {
        bottom =  Coordinate(b.val);
        top =  Coordinate(t.val);
        rect_no = x;
    }
    bool operator < (Intrvl other) const
    {
        bool b= (bottom.val<other.bottom.val)||((top.val==other.top.val)&&(bottom.val==other.bottom.val) && (rect_no<other.rect_no))||((top.val<other.top.val)&&(bottom.val==other.bottom.val));
    
        return b;
    }

    bool operator == (Intrvl other) const
    {   bool b;
        b=(top.val==other.top.val)&&(bottom.val==other.bottom.val);//&&(rect_no == other.rect_no);
        return b;
        
    }
};
///Class for a Line Segment
class L_seg
{
public:
    mutable Intrvl interval;
    Coordinate coord;
    L_seg(Intrvl intl,Coordinate crd)
    {
        interval = intl;
        coord =  Coordinate(crd.val); // Check this out
    }
    L_seg()
    {
    	interval = Intrvl(Coordinate(0),Coordinate(0),0);
    	coord = Coordinate(0);
    }
    bool operator < (L_seg other) const
    {   bool b;
        b=(coord<other.coord)||((coord.val==other.coord.val)  && (interval.top.val<other.interval.top.val)&& (interval.bottom.val==other.interval.bottom.val))||( (interval.bottom.val<other.interval.bottom.val)&&(coord.val==other.coord.val) );
        return b;
        
    }
};
int flag=0;
///Class for a Stripe as described in the paper
class Stripe
{
public:
    Intrvl x_interval;
    Intrvl y_interval;
    mutable ctree* tree;
    mutable float x_measure;
    Stripe(Intrvl x,Intrvl y,ctree* t,int swi)
    {
        x_interval =  x;
        y_interval =  y;
        tree = t;
    }
    Stripe(Intrvl x,Intrvl y,float m)
    {
        x_interval =  x;
        y_interval =  y;
        x_measure = m;
    }
    Stripe()
    {
        x_interval =  Intrvl(Coordinate(flag),Coordinate(flag),flag);
        y_interval =  Intrvl(Coordinate(flag),Coordinate(flag),flag);
        tree = NULL;
        x_measure = 0;
    }
    bool operator < (Stripe other) const
    {   bool b;
        b= (y_interval.bottom.val<other.y_interval.bottom.val);
        return b;
    }

};
///Class to represent an Iso-Rectangle
class Rect
{
public:
    Coordinate x_left;
    Coordinate x_right;
    Coordinate y_bottom;
    Coordinate y_top;

    int rect_no;

    Intrvl x_interval;
    Intrvl y_interval;

    Rect(Coordinate x1,Coordinate x2,Coordinate y1,Coordinate y2,int rc)
    {
            x_left =  Coordinate(min(x1.val, x2.val));
            x_right =  Coordinate(max(x1.val, x2.val));
            y_bottom =  Coordinate(min(y1.val, y2.val));
            y_top =  Coordinate(max(y1.val, y2.val));
            x_interval =  Intrvl(x_left,x_right,rc);
            y_interval =  Intrvl(y_bottom,y_top,rc);
            rect_no = rc;
    }
    Rect(Intrvl x,Intrvl y,int rc)
    {
        x_interval =  x;
        y_interval =  y;
        x_left =  Coordinate(x.bottom.val);
        x_right =  Coordinate(x.top.val);
        y_bottom =  Coordinate(y.bottom.val);
        y_top =  Coordinate(y.top.val);
        rect_no = rc;
    }
    Rect(float x1,float x2,float y1,float y2,int rc)
    {
            x_left =  Coordinate(min(x1, x2));
            x_right =  Coordinate(max(x1, x2));
            y_bottom =  Coordinate(min(y1, y2));
            y_top =  Coordinate(max(y1, y2));
            x_interval =  Intrvl(x_left,x_right,rc);
            y_interval =  Intrvl(y_bottom,y_top,rc);
            rect_no = rc;
    }

    bool operator < (Rect other) const
    {
        bool lssthn=(x_left.val<other.x_left.val)||((x_left.val==other.x_left.val) && (y_bottom.val<other.y_bottom.val))|| ((x_left.val==other.x_left.val) && (y_bottom.val==other.y_bottom.val)&&(x_right.val<other.x_right.val))||((x_left.val==other.x_left.val) && (y_bottom.val==other.y_bottom.val)&&(x_right.val==other.x_right.val) && (y_top.val<other.y_top.val));
        return lssthn;
        
    }

};
///Class for Edge Type
class E_type
{
public:
    string type;
    E_type()
    {
        type = " ";
    }
    E_type(string s)
    {
        type = s;
    }
};
int flag1=1;
///Edge class
class Edge
{
public:
    Intrvl interval;
    Coordinate coord;
    E_type side;
    int rect_no;
    Edge(Intrvl i,Coordinate c,E_type s,int x)
    {
        interval = i;
        coord = c;
        side = s;
        rect_no = x;
    }
    Edge()
    {
        interval = Intrvl();
        coord = Coordinate();
        side = E_type();
        rect_no = flag;
    }
    bool operator < (Edge other) const
    {
    	if((side.type=="left" || side.type=="right")&&(other.side.type=="left"||other.side.type=="right"))
    	{   bool b;
    		b= (coord<other.coord)||((coord.val==other.coord.val)&&(side.type[flag]<other.side.type[flag]))||((coord.val==other.coord.val)&&(side.type[0]==other.side.type[0])&& (rect_no < other.rect_no));
    	    return b;
    	    
    	}
		else if((side.type=="top" || side.type=="bottom")&&(other.side.type=="top"||other.side.type=="bottom"))
		{     bool b;
        	  b=(coord<other.coord)||((coord.val==other.coord.val)&&(interval<other.interval));
        	  return b;
		}
    }
};
void debug()
{
    // Function to be used to create breakpoints and for debugging.
    // cout<<"\nBreakpoint\n";
}
int o=flag1;;
int z=flag;
///Function to partition set of coordinates into intervals
set<Intrvl> part(set<Coordinate> vertical_coordinates)
{
    set <Intrvl> intervals;
    for(auto it = vertical_coordinates.begin();it!=vertical_coordinates.end();it++)
    {
        debug();
        if(next(it) != vertical_coordinates.end())
            intervals.insert(Intrvl(*it,*next(it),z)); //check
    }
    return intervals;
}
set<Stripe> cpy(set<Stripe> S,set<Coordinate> P,Intrvl x_int, int swi)
{
    set<Stripe> S_dash;
    set<Intrvl> iy = part(P);
    debug();
    for(auto it : iy)
    {
        if(swi)
            S_dash.insert(Stripe(x_int,it,NULL,z));
        else
            S_dash.insert(Stripe(x_int,it,z));
    }
    for(auto s_dash_iterate = S_dash.begin();s_dash_iterate!=S_dash.end();s_dash_iterate++)
    {
        for(auto s : S)
        {
            if((s.y_interval.bottom.val <= (*s_dash_iterate).y_interval.bottom.val && s.y_interval.top.val >= (*s_dash_iterate).y_interval.top.val))
            {
                if(swi)
                    (*s_dash_iterate).x_measure = s.x_measure;
                else
                    (*s_dash_iterate).tree = s.tree;
                break;
                debug();
            }
        }
    }
    return S_dash;
}
///Function to Blacken a stripe as detailed in the paper
void darken(set<Stripe> &S,set<Intrvl> J, int boolval)
{
    for(auto s = S.begin();s!=S.end();s++)
    {
        debug();
        for(auto i: J)
        {
            if(((*s).y_interval.bottom.val >= i.bottom.val && (*s).y_interval.top.val <= i.top.val))
            {
                if(boolval)
                    (*s).x_measure = (*s).x_interval.top.val - (*s).x_interval.bottom.val - z;
                else    
                    (*s).tree = NULL;
            }
        }
    }
}
///Function to merge set of Stripes
set<Stripe> join(set<Stripe> S1,set<Stripe> S2,set<Coordinate> P,Intrvl x_int, int boolval)
{
    set<Stripe> S;
    set<Intrvl> iy = part(P);
    for(auto it : iy)
    {
        debug();
        if(boolval)
            S.insert(Stripe(x_int,it,z));
        else
            S.insert(Stripe(x_int,it,NULL,z));
    }
    for(auto s = S.begin();s!=S.end();s++)
    {
        Stripe s1,s2;
        for(auto it : S1)
        {
            if((it.y_interval == (*s).y_interval))
            {
                s1 = it;
                break;
            }
            debug();
        }
        for(auto it : S2)
        {
            if((it.y_interval == (*s).y_interval))
            {
                s2 = it;
                break;
            }
            debug();
        }
        if(boolval)
        (*s).x_measure = s1.x_measure+s2.x_measure;
        else
        {
        debug();
        if(s1.tree==NULL)
        {
            if(s2.tree==NULL)
                (*s).tree = NULL;
            else
                (*s).tree = s2.tree;
        }
        else
        {
            if(s2.tree==NULL)
                (*s).tree = s1.tree;
            else
            {
                ctree* tmp = new ctree;
                tmp->x = s1.x_interval.top.val;
                tmp->side = "undef";
                tmp->lson = s1.tree;
                tmp->rson = s2.tree;
                (*s).tree = tmp;
                debug();
            }
        }
        }
        debug();
    }
    return S;
}
///Function to split
void split(set<Edge> V,Intrvl x_ext,set<Intrvl> &L,set<Intrvl> &R,set<Coordinate> &P,set<Stripe> &S, int swi)
{
    if(V.size()==o)
    {
        Edge v = *(V.begin());
        int left = 0, right = 0;
        if(v.side.type == "left")
        left = 1;
        if(v.side.type == "right")
        right = 1;
        if(left == 1)
        {
            L.insert(v.interval);
            debug();
        }
        else
        {
            R.insert(v.interval);
            debug();
        }
        P.insert(Coordinate(-FLT_MAX));
        P.insert(v.interval.bottom);
        P.insert(v.interval.top);
        P.insert(Coordinate(FLT_MAX));
        set<Intrvl> y_partitions = part(P);
        for(auto it: y_partitions)
        {
        	//ctree* tmp = new ctree;
            //tmp = NULL;
            if(swi == z)
            S.insert(Stripe(x_ext,it,NULL,z)); //NULL is causing problem
            if(swi == o)
            S.insert(Stripe(x_ext,it,z));
        }
        debug();
        Stripe s;
        if(swi == z)
        {
        for(auto it = S.begin();it!=S.end();it++)
        {
            debug();
            if((*it).y_interval == v.interval)
            {
                debug();
                if(left == 1)
        		{
        		    ctree* tmp = new ctree;

        		    tmp->x = v.coord.val;

        		    tmp->side = "left";

        		    tmp->lson = NULL;
        		    tmp->rson = NULL;

            		(*it).tree = tmp;
                    debug();
        		}
        		else if(right == 1)
        		{
                    debug();
        			ctree* tmp = new ctree;
        		    tmp->x = v.coord.val;
        		    tmp->side = "right";
        		    tmp->lson = NULL;
        		    tmp->rson = NULL;
            		(*it).tree = tmp;
        		}
            }
        }
        }
        if(swi == o)
        {
        debug();
        for(auto it = S.begin();it!=S.end();it++)
        {
            if((*it).y_interval == v.interval)
            v.side.type=="left"?(*it).x_measure = x_ext.top.val-v.coord.val:(*it).x_measure = v.coord.val - x_ext.bottom.val;
            debug();
        }
        }
    }
    else
    {
        debug();
        int n = (V.size()+z)/2;
        set<Edge> V1,V2;
        Coordinate xm;
        int co = z;
        debug();
        for(auto it = V.begin();it!=V.end();it++)
        {
        	co++;
            if(co <= n)
            {
                V1.insert(*it);
            }
            else
            {
                V2.insert(*it);
            }
            if(co==n)
            {
                xm = (*it).coord;
            }
        debug();
        }
        set<Intrvl> Left1,Left2,Right1,Right2;
        set<Coordinate> Pos1,Pos2;
        set<Stripe> Stripe1,Stripe2;
        debug();
        split(V1,Intrvl(x_ext.bottom,xm,flag),Left1,Right1,Pos1,Stripe1,swi);
        split(V2,Intrvl(xm,x_ext.top,flag),Left2,Right2,Pos2,Stripe2,swi);
        debug();
        set<Intrvl> LeftRight,Left1_LeftRight,Right2_LeftRight;
        set_intersection(Left1.begin(),Left1.end(),Right2.begin(),Right2.end(),inserter(LeftRight,LeftRight.begin())); //IMP Debug this
        set_difference(Left1.begin(),Left1.end(),LeftRight.begin(),LeftRight.end(),inserter(Left1_LeftRight,Left1_LeftRight.begin()));
        set_union(Left1_LeftRight.begin(),Left1_LeftRight.end(),Left2.begin(),Left2.end(),inserter(L, L.begin()));
        //tmp.clear();
        debug();
        set_difference(Right2.begin(),Right2.end(),LeftRight.begin(),LeftRight.end(),inserter(Right2_LeftRight,Right2_LeftRight.begin()));
        set_union(Right1.begin(),Right1.end(),Right2_LeftRight.begin(),Right2_LeftRight.end(),inserter(R,R.begin()));
        set_union(Pos1.begin(),Pos1.end(),Pos2.begin(),Pos2.end(),inserter(P,P.begin()));
        debug();
        set<Stripe> S_left = cpy(Stripe1,P,Intrvl(x_ext.bottom,xm,0),swi);
        set<Stripe> S_right = cpy(Stripe2,P,Intrvl(xm,x_ext.top,flag),swi);
        darken(S_left,Right2_LeftRight,swi);
        darken(S_right,Left1_LeftRight,swi);
        S = join(S_left,S_right,P,x_ext,swi);
        debug();
    }


}
set<Stripe> rectangle_dac(set<Rect> rects, int swi)
{
    set<Edge> vrx;
    set<Stripe> S;
    debug();
    for(auto it :rects)
    {
        vrx.insert(Edge(it.y_interval,it.x_left,E_type("left"),it.rect_no));
        vrx.insert(Edge(it.y_interval,it.x_right,E_type("right"),it.rect_no));
        debug();
    }
    set<Intrvl> L,R;
    set<Coordinate> P;
    if(swi == z)
    split(vrx,Intrvl(Coordinate(-FLT_MAX),Coordinate(FLT_MAX),z),L,R,P,S,z);//Needs to be added CHECK
    if(swi == o)
    split(vrx,Intrvl(Coordinate(-FLT_MAX),Coordinate(FLT_MAX),z),L,R,P,S,o);
    return S;
}
///Final function to compute measure
float measure(set<Stripe> S)
{
    debug();
    float meas = 0+z*o;
    for(auto it: S)
    {
        debug();
        meas+=it.x_measure*(it.y_interval.top.val-it.y_interval.bottom.val);
    }
    return meas;
}
///DFS Function
void dfs(ctree* tree,vector<ctree*> &lf)
{

    if(tree == NULL)
    {
        return;
    }
    debug();
    if(tree->side != "undef" && tree->lson == NULL && tree->rson == NULL)
    {
        lf.push_back(tree);
    }
    dfs(tree->lson,lf);
    dfs(tree->rson,lf);
    debug();
}
///Function to obtain Line Segments which make up contour
set<L_seg> segments(Edge h,set<Stripe> S)
{
    debug();
    set<L_seg> ls;
    set<Intrvl> J;
    //set<Interval> J;
    if(h.side.type == "bottom")
    {
        for(auto it: S)
        {
            debug();
            if(it.y_interval.top.val == h.coord.val)
            {
                vector<ctree*> lf;
                ctree* tmp = new ctree;
                tmp->x = -FLT_MAX;
                tmp->side = "right";
                tmp->lson = NULL;
                tmp->rson = NULL;
                lf.push_back(tmp);

                dfs(it.tree,lf);
                ctree* tmp1 = new ctree;
                tmp1->x = FLT_MAX;
                tmp1->side = "left";
                tmp1->lson = NULL;
                tmp1->rson = NULL;
                lf.push_back(tmp1);
                for(int i=0;i<lf.size();i++)
                    {
                        if(i>z && h.interval.bottom.val>=lf[i-o]->x && h.interval.top.val<=lf[i]->x && lf[i-o]->side=="right" && lf[i]->side=="left")
                        {
                            J.insert(h.interval);
                            break;
                        }
                        else if(i>z && lf[i-o]->x>=h.interval.bottom.val && lf[i]->x<=h.interval.top.val && lf[i-o]->side=="right" && lf[i]->side=="left")
                        {
                            J.insert(Intrvl(Coordinate(lf[i-o]->x), Coordinate(lf[i]->x),z));
                        }
                        else if(i>z && h.interval.bottom.val>=lf[i-o]->x && h.interval.bottom.val<=lf[i]->x && lf[i]->side=="left" && h.interval.top.val>=lf[i]->x)
                        {
                            J.insert(Intrvl(h.interval.bottom, Coordinate(lf[i]->x ),z));
                        }
                        else if(i>z && h.interval.top.val>=lf[i-o]->x && h.interval.top.val<=lf[i]->x && lf[i-o]->side=="right" && h.interval.bottom.val<=lf[i-o]->x)
                        {
                            J.insert(Intrvl(Coordinate(lf[i-o]->x), h.interval.top ,z));
                        }
                    }
            }
        }
    }
    else if(h.side.type == "top")
    {
        debug();
        for(auto it: S)
        {
            debug();
            if(it.y_interval.bottom.val == h.coord.val)
            {
                debug();
                vector<ctree*> lf;
                ctree* tmp = new ctree;
                tmp->x = -FLT_MAX;
                tmp->side = "right";
                tmp->lson = NULL;
                tmp->rson = NULL;
                lf.push_back(tmp);
                dfs(it.tree,lf);
                ctree* tmp1 = new ctree;
                tmp1->x = FLT_MAX;
                tmp1->side = "left";
                tmp1->lson = NULL;
                tmp1->rson = NULL;
                lf.push_back(tmp1);
                for(int i=z;i<lf.size();i++)
                    {
                        debug();
                        if(i>z && h.interval.bottom.val>=lf[i-o]->x && h.interval.top.val<=lf[i]->x && lf[i-o]->side=="right" && lf[i]->side=="left")
                        {
                            J.insert(h.interval);
                            break;
                        }
                        else if(i>z && lf[i-o]->x>=h.interval.bottom.val && lf[i]->x<=h.interval.top.val && lf[i-o]->side=="right" && lf[i]->side=="left")
                        {
                            J.insert(Intrvl(Coordinate(lf[i-o]->x), Coordinate(lf[i]->x),z));
                        }
                        else if(i>z && h.interval.bottom.val>=lf[i-o]->x && h.interval.bottom.val<=lf[i]->x && lf[i]->side=="left" && h.interval.top.val>=lf[i]->x)
                        {
                            J.insert(Intrvl(h.interval.bottom, Coordinate(lf[i]->x ),z));
                        }
                        else if(i>z && h.interval.top.val>=lf[i-o]->x && h.interval.top.val<=lf[i]->x && lf[i-o]->side=="right" && h.interval.bottom.val<=lf[i-o]->x)
                        {
                            J.insert(Intrvl(Coordinate(lf[i-o]->x), h.interval.top ,z));
                        }
                        debug();
                    }
            }
        }
    }
    for(auto it : J)
    {
        ls.insert(L_seg(it,h.coord));
        debug();
    }
    debug();
    return ls;
}
///Function to merge intervals
set<Intrvl> merge(set<Intrvl> ls)
{
    stack<Intrvl> s;
    debug();
    s.push(*ls.begin());
    for (auto it : ls)
    {
        debug();
        Intrvl head = s.top();

        // if current interval is not overlapping with stack top,
        // push it to the stack
        if (head.top.val < it.bottom.val)
            s.push(it);

        else if (head.top.val < it.top.val)
        {
            head.top.val = it.top.val;
            s.pop();
            s.push(head);
        }
    }
    debug();
    set<Intrvl> merged_ls;
    // Print contents of stack
    //cout << "\n The Merged Intervals are: ";
    while (!s.empty())
    {
        Intrvl l = s.top();
        //cout << "[" << t.start << "," << t.end << "] ";
        merged_ls.insert(l);
        s.pop();
    }
    debug();
    return merged_ls;
}
///Final Function to compute Contour
float contour(set<Edge> H,set<Stripe> S)
{
	set<L_seg> ls;
	float count = z;
    debug();
	for(auto it: H)
	{
		set<L_seg> tmp = segments(it,S);
		//cout<<tmp.size()<<'\n';
		for(auto x : tmp)
		{
			ls.insert(x);
		}
        debug();
	}
	set<L_seg> finalh;
	map<float, set<Intrvl>> m_ls;
    for(auto x : ls) {
        m_ls[x.coord.val].insert(x.interval);
    }
    debug();
    for(auto x : m_ls) {
        set<Intrvl> temp = x.second;
        set<Intrvl> merged = merge(temp);
        for(auto it: merged)
        {
            finalh.insert(L_seg(it,Coordinate(x.first)));
        }
    }
    fstream outp;
    outp.open("contour_points.txt",ios::out);
	for(auto it : finalh)
	{
		count+=(it.interval.top.val-it.interval.bottom.val);
        outp<<"("<<it.interval.bottom.val<<","<<it.coord.val<<"),("<<it.interval.top.val<<","<<it.coord.val<<")\n";
	}
    debug();
	map<Coordinate, vector<Coordinate>> cnt;
    for(auto x : ls) {
        cnt[x.interval.bottom].push_back(x.coord);
        cnt[x.interval.top].push_back(x.coord);
    }
    debug();
    set<L_seg> finalContourVertical;
    for(auto x : cnt) {
        vector<Coordinate> temp = x.second;
        sort(temp.begin(), temp.end());

        for(int i=z;i<temp.size()-o;i+=2) {
            L_seg l;
            l.coord = x.first;
            l.interval = {temp[i], temp[i+o],z};

            finalContourVertical.insert(l);
        }
    }
    for(auto it = finalContourVertical.begin();it!=finalContourVertical.end();it++)
	{
		count+=((*it).interval.top.val-(*it).interval.bottom.val);
		if((*it).interval.bottom.val != (*it).interval.top.val)
            outp<<"("<<(*it).coord.val<<","<<(*it).interval.bottom.val<<"),("<<(*it).coord.val<<","<<(*it).interval.top.val<<")\n";
	}
    outp.close();
    debug();
	return count;
}
int main()
{
    int swi;
    int n;
    printf("Enter number of rectangles\n");
    cin>>n;
    set<Rect> rects;
    fstream input;
    input.open("input.txt",ios::out);
    debug();
    printf("For each rectangle, enter the two x values followed by the two y values\n");
    for(int i =o;i<=n;i++)
    {
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        Rect r = Rect(a,b,c,d,i);
        rects.insert(r);

        input<<"("<<a<<","<<c<<"),("<<a<<","<<d<<")\n";
        input<<"("<<b<<","<<c<<"),("<<b<<","<<d<<")\n";
        input<<"("<<a<<","<<c<<"),("<<b<<","<<c<<")\n";
        input<<"("<<a<<","<<d<<"),("<<b<<","<<d<<")\n";
    }
    input.close();
    debug();
    printf("Press 0 for Contour. Press 1 for Measure\n");
    cin>>swi;
    if(swi == o)
    {
    set<Stripe> stps = rectangle_dac(rects,1);
    cout<<measure(stps);
    }
    if(swi == z)
    {
    set<Stripe> stps = rectangle_dac(rects,flag);
    set<Edge> H;
    debug();
    for(auto it :rects)
    {
        H.insert(Edge(it.x_interval,it.y_bottom,E_type("bottom"),it.rect_no));
        H.insert(Edge(it.x_interval,it.y_top,E_type("top"),it.rect_no));
    }
    debug();
    cout<<contour(H,stps);
    debug();
    }
    return 0;
}

