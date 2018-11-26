import java.util.*;
class Hospital{
	class Doctor{
		String id;
		String registration_no;
		String doc_name;
	}
	class Experiment{
		String exp;
		String result;
		public Experiment(String exp,String result){
			this.exp=exp;
			this.result=result;
		}
	}
	class Patient extends Doctor{
		static final String error="ERR_ID";
		String social_security;
		String name;
		Hashtable<String,Experiment> h;
		public void input(String social_security,Patient pat[],int count){
			Scanner sc=new Scanner(System.in);
			this.social_security=social_security;
			System.out.println("\nEnter the name of the patient\n");
			String name=sc.nextLine();
			this.name=name;
			System.out.println("\nEnter the name of the doctor\n");
			name=sc.nextLine();
			super.doc_name=name;
			boolean b=is_available_doctor(name,pat,count);
			if(b==false){
				System.out.println("\nEnter the registration no. of the doctor\n");
				String rgs=sc.nextLine();
				super.registration_no=rgs;
				System.out.println("\nEnter the ID of the doctor\n");
				String id=sc.nextLine();
				super.id=id;
			}
			else if(b==true){
				super.registration_no=get_rgs(name,pat,count);
				super.id=get_id(name,pat,count);
			}
			h=new Hashtable<String,Experiment>();
		}
		public boolean is_available_doctor(String name,Patient pat[],int count){
			for(int i=0;i<count;i++){
				if(name.equals(pat[i].doc_name)){
					return(true);
				}
			}
			return(false);
		}
		public String get_rgs(String name,Patient pat[],int count){
			for(int i=0;i<count;i++){
				if(name.equals(pat[i].doc_name)){
					return(pat[i].registration_no);
				}
			}
			return(error);
		}
		public String get_id(String name,Patient pat[],int count){
			for(int i=0;i<count;i++){
				if(name.equals(pat[i].doc_name)){
					return(pat[i].id);
				}
			}
			return(error);
		}
		public void display(){
			System.out.println("\nSocial security number:"+this.social_security);
			System.out.println("\nName of the patient:"+this.name);
			System.out.println("\nName of the doctor:"+super.doc_name);
			System.out.println("\nRegistration no of the doctor:"+super.registration_no);
			System.out.println("\nID of the doctor:"+super.id);
		}
		public void set_record(){
			Scanner sc=new Scanner(System.in);
			System.out.println("\nenter the name of the experiment:");
			String exp=sc.nextLine();
			if(!h.containsKey(exp)){
				System.out.println("\nEnter the result:");
				String result=sc.nextLine();
				Experiment e=new Experiment(exp,result);
				h.put(exp,e);
			}
			else{
				System.out.println("Result available");
				Experiment e=h.get(exp);
				System.out.println("\nName of the experiment:"+e.exp);
				System.out.println("\nResult of the experiment:"+e.result);
			}
		}
		public void access(){
			System.out.println("\n\nPATIENT DETAILS:------->\n\n");
			System.out.println("Doctor's name:"+super.doc_name);
			System.out.println("Doctor's registration no:"+super.registration_no);
			System.out.println("Doctor's id:"+super.id);
			System.out.println("Social security no is:"+social_security);
			System.out.println("Name of the patient is:"+name);
			Iterator<String> itr=h.keySet().iterator();
			while(itr.hasNext()){
				Experiment e=h.get(itr.next());
				System.out.println("Name of the experiment:"+e.exp);
				System.out.println("Result of the experiment:"+e.result);
				System.out.println();
			}
		}
	}
	public int is_new_patient(Patient pat[],int count,String social_security){
		for(int i=0;i<count;i++){
			if(social_security.equals(pat[i].social_security)){
				return(i);
			}
		}
		return(-1);
	}
	public void display(Patient pat[],int count){
		System.out.println("\nThe available social security numbers for admitted patients are:\n");
		for(int i=0;i<count;i++){
			System.out.println(pat[i].social_security);
		}
	}
	public void util(){
		Scanner sc=new Scanner(System.in);
		int choice=-1;
		Patient pat[]=new Patient[100];
		int count=0;
		int pchoice;
		do{
			/*System.out.println("\nContinue program?\n(1)yes\n(2)no\n");
			choice=sc.nextInt();
			*/
			//if(choice==1){
				System.out.println("\nEnter your choice:\n\t(1)patient entry\n\t(2)report any observation\n\t(3) check outs\n\t(0) To exit\n");
				pchoice=sc.nextInt();
				if(pchoice==1){
					System.out.println("\nEnter the patient code:\n");
					String temp=sc.nextLine();
					String social_security=sc.nextLine();
					int x=is_new_patient(pat,count,social_security);
					if(x==-1){
						pat[count]=new Patient();
						pat[count].input(social_security,pat,count);
						count++;
					}
					else{
						System.out.println("\nOld Patient\n");
						pat[x].display();
					}
				}
				else if(pchoice==2){
					if(count!=0)
					display(pat,count);
					System.out.println("\nEnter the social security no\n");
					String temp=sc.nextLine();
					String social_security=sc.nextLine();
					int x=is_new_patient(pat,count,social_security);
					if(x!=-1){
						pat[x].set_record();
					}
					else{
						System.out.println("INVALID SOCIAL SECURITY");
					}
				}
				else if(pchoice==3){
					if(count!=0)
					display(pat,count);
					System.out.println("\nEnter the social security no\n");
					String temp=sc.nextLine();
					String social_security=sc.nextLine();
					int x=is_new_patient(pat,count,social_security);
					if(x!=-1){
						pat[x].access();
					}
					else{
						System.out.println("INVALID SOCIAL SECURITY");
					}
				}
				else if(pchoice==0){
				return;
			}
		}while(pchoice!=0);
	}
	public static void main(String []args){
		Hospital obj=new Hospital();
		obj.util();
	}
}
