using System;
using System.Runtime.InteropServices;

namespace TestRapidJsonLib.net
{

	class Program
	{
		[DllImport("RapidJsonLib.dll", CallingConvention = CallingConvention.Cdecl)]
		public static extern int CreateContext(ref IntPtr ctx);

		[DllImport("RapidJsonLib.dll", CallingConvention = CallingConvention.Cdecl)]
		public static extern int DestoryContext(IntPtr ctx);

		[DllImport("RapidJsonLib.dll", CallingConvention = CallingConvention.Cdecl)]
		public static extern int load(IntPtr ctx);

		[DllImport("RapidJsonLib.dll", CallingConvention = CallingConvention.Cdecl)]
		public static extern void SetJsonPath(IntPtr ctx, string path);

		//[DllImport("RapidJsonLib.dll", CallingConvention = CallingConvention.Cdecl)]
		//public static extern int ModifyNode_s(IntPtr ctx, string father, string child, string value);//是否有效

		//[DllImport("RapidJsonLib.dll", CallingConvention = CallingConvention.Cdecl)]
		//public static extern int ModifyNode_i(IntPtr ctx, string father, string child, int value);//是否有效

		//[DllImport("RapidJsonLib.dll", CallingConvention = CallingConvention.Cdecl)]
		//public static extern int ModifyNode_b(IntPtr ctx, string father, string child, bool value);//是否有效

		//[DllImport("RapidJsonLib.dll", CallingConvention = CallingConvention.Cdecl)]
		//public static extern int ModifyNode_f(IntPtr ctx, string father, string child, float value);//是否有效

		//[DllImport("RapidJsonLib.dll", CallingConvention = CallingConvention.Cdecl)]
		//public static extern int RemoveNode(IntPtr ctx, string father, string child);//是否有效

		//[DllImport("RapidJsonLib.dll", CallingConvention = CallingConvention.Cdecl)]
		//public static extern int AddNode_s(IntPtr ctx, string father, string child, string value);//是否有效

		//[DllImport("RapidJsonLib.dll", CallingConvention = CallingConvention.Cdecl)]
		//public static extern int AddNode_i(IntPtr ctx, string father, string child, int value);//是否有效

		//[DllImport("RapidJsonLib.dll", CallingConvention = CallingConvention.Cdecl)]
		//public static extern int AddNode_b(IntPtr ctx, string father, string child, bool value);//是否有效

		//[DllImport("RapidJsonLib.dll", CallingConvention = CallingConvention.Cdecl)]
		//public static extern int AddNode_f(IntPtr ctx, string father, string child, float value);//是否有效

		//[DllImport("RapidJsonLib.dll", CallingConvention = CallingConvention.Cdecl)]
		//public static extern int GetNode_s(IntPtr ctx, string father, string child, IntPtr value);//是否有效

		[DllImport("RapidJsonLib.dll", CallingConvention = CallingConvention.Cdecl)]
		public static extern int GetNode_i(IntPtr ctx, ref int value, int n, __arglist);//是否有效

		//[DllImport("RapidJsonLib.dll", CallingConvention = CallingConvention.Cdecl)]
		//public static extern int GetNode_b(IntPtr ctx, string father, string child, ref bool value);//是否有效

		//[DllImport("RapidJsonLib.dll", CallingConvention = CallingConvention.Cdecl)]
		//public static extern int GetNode_f(IntPtr ctx, string father, string child, ref float value);//是否有效

		static void Main(string[] args)
		{
			IntPtr ctx = IntPtr.Zero;
			CreateContext(ref ctx);
			SetJsonPath(ctx, "./test.json");
			int dst = 0;
			GetNode_i(ctx, ref dst, 3, __arglist("SHAANXI", "Obj", "age"));
			//AddNode_s(ctx, "test_new_father_Node", "LLLLSK","333");
			//ModifyNode_s(ctx, "bei_jing", "LLLLSK", "你好");
			//IntPtr ret = Marshal.AllocHGlobal(100);
			//GetNode_s(ctx, "bei_jing", "LLLLSK", ret);
			//string value = Marshal.PtrToStringAnsi(ret);
			//Console.WriteLine(value);
			////RemoveNode(ctx, "bei_jing", "LLLLSK");
			//Marshal.FreeHGlobal(ret);
			DestoryContext(ctx);                                                                                                                                                                                                                                                                                                                           
			Console.ReadKey();
		}
	}
}